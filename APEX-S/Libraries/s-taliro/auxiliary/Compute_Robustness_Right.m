function [cost, ind, cur_par, rob] = Compute_Robustness_Right(inputModel,inputModelType,inpArray)
% Compute_Robustness_Right - Computes the robustness of a simulation trajectory
% generated by the parameters passed in the input arguments
%
%
% (C) 2010, Yashwanth Annapureddy, Arizona State University
% (C) 2010, Georgios Fainekos, Arizona State University
% (C) 2012, Bardh Hoxha, Arizona State University
% (C) 2013, Houssam Abbas, Arizona State University

global staliro_mtlFormula;
global staliro_Predicate;
global staliro_SimulationTime;
global staliro_InputBounds;
global temp_ControlPoints;
global staliro_dimX;
global staliro_opt;
global staliro_ParameterIndex;
global staliro_Polarity;
global staliro_parameter_list;
global staliro_inpRangeUnscaled;

Rcmap = rcmap.instance();
% Check whether a parameter search is running and if so get the current
% parameters from the end position of the input array.
% Since inpArray contains current parameters at the end of the array we do
% not include the parameter values in XPoint and UPoint

% rescale back to the original range for robustness computation
if staliro_opt.normalization == 1 
    paramBeginIndex = size(inpArray,1) - size(staliro_ParameterIndex,2) + 1;
    inpArray(paramBeginIndex:end,:) = (inpArray(paramBeginIndex:end,:)).*(staliro_inpRangeUnscaled(paramBeginIndex:end,2)-staliro_inpRangeUnscaled(paramBeginIndex:end,1))+staliro_inpRangeUnscaled(paramBeginIndex:end,1);
end

XPoint = inpArray(1:staliro_dimX);
if staliro_opt.parameterEstimation > 0
    if staliro_opt.param_est_fals_stage == 1
        temp_par = vertcat(staliro_Predicate(staliro_ParameterIndex).range);
        if isequal(staliro_Polarity,-1);
            cur_par = temp_par(:,2);
        else isequal(staliro_Polarity,1);
            cur_par = temp_par(:,1);
        end
        inpArray(end - size(staliro_ParameterIndex,2) + 1:end) = cur_par;
    else
        cur_par = inpArray(end - size(staliro_ParameterIndex,2) + 1:end);
    end
    UPoint = inpArray(staliro_dimX+1:end - size(staliro_ParameterIndex,2));
else
    cur_par = [];
    UPoint = inpArray(staliro_dimX+1:end);
end

ind = 1;
%T = []; XT = []; YT = []; LT = []; CLG = []; GRD = [];

[hs, rc] = systemsimulator(inputModel, XPoint, UPoint, staliro_SimulationTime, staliro_InputBounds, temp_ControlPoints);

if rc == Rcmap.int('RC_SIMULATION_FAILED')
    cost = NaN;
    rob = NaN;
    warning('Simulation failed - results are unreliable, robustness set to NaN');
end

T = hs.T;
XT = hs.XT;
YT = hs.YT;
LT = hs.LT;
CLG = hs.CLG;
GRD = hs.GRD;

%% Compute robustness of trajectory
if staliro_opt.spec_space=='X' && ~isempty(XT)
    STraj = XT;
elseif staliro_opt.spec_space=='Y' && ~isempty(YT)
    STraj = YT;
else
    err_msg = sprintf('S-Taliro: The selected specification space (spec_space) is not supported or the signal space is empty.\n If you are using a "white box" m-function as a model, then you must set the "spec_space" to "X".');
    error(err_msg)
end

%% Set the dimensions of the output values that taliro will work with
if ~isempty(staliro_opt.dim_proj)
    STraj = STraj(:,staliro_opt.dim_proj);
end


%% Reduce granularity of STraj when too big and causes taliro to run out of memory - REVIEW CAREFULLY

if staliro_opt.taliro_undersampling_factor ~= 1
    STraj = STraj(1:staliro_opt.taliro_undersampling_factor:end,:);
    T = T(1:staliro_opt.taliro_undersampling_factor:end,:);
end

if isempty(staliro_mtlFormula) && strcmp(inputModelType, 'hautomaton')
    [nearest_point_on_s, tmin, tmp_rob] = DistTrajToUnsafe([T STraj]', inputModel.unsafe);
    
elseif ~isempty(staliro_mtlFormula)
    
    %% Get polarity and set the fcn_cmp
    % Update the predicates in pred_temp with the current parameter.Also 
    % set the state or timing parameter for each predicate that has a
    % parameter
    pred_tmp = staliro_Predicate;
    
    if ~isempty(staliro_Polarity)
        if isequal(staliro_Polarity, -1)
            fcn_cmp = @le;
            
        elseif isequal(staliro_Polarity, 1)
            fcn_cmp = @ge;
        end
        for ii=1:size(staliro_ParameterIndex,2)
            if staliro_parameter_list(staliro_ParameterIndex(ii)) == 2
                pred_tmp(staliro_ParameterIndex(ii)).value = cur_par(ii);
            elseif staliro_parameter_list(staliro_ParameterIndex(ii)) == 3
                pred_tmp(staliro_ParameterIndex(ii)).value = cur_par(ii);
                pred_tmp(staliro_ParameterIndex(ii)).b = cur_par(ii);
            else
                error('Staliro: Parameter setting error, check the predicate settings.');
            end
        end
    end
    
    % Check whether the staliro_options obj is set to run dp_taliro
    %   or dp_t_taliro
    % It is necessary to handle the different cases since: 1.The feval function
    %   returns a different type of object based on the options set and, 2.For
    %   proper error condition checking
    
    if isequal(staliro_opt.taliro, 'dp_taliro') || isequal(staliro_opt.taliro, 'fw_taliro')
        
        switch staliro_opt.taliro_metric
            case 'none'
                tmp_rob = feval(staliro_opt.taliro, staliro_mtlFormula, pred_tmp, STraj, T);
            case 'hybrid_inf'
                if isempty(LT) || isempty(CLG)
                    error('S-Taliro: The location trace or the Control Location Graph are empty')
                else
                    tmp_rob = feval(staliro_opt.taliro, staliro_mtlFormula, pred_tmp, STraj, T, LT, CLG);
                end
            case 'hybrid'
                if isempty(LT) || isempty(CLG) || isempty(GRD)
                    error('S-TaLiRo: The location trace or the Control Location Graph or the Guard set are empty')
                else
                    tmp_rob = feval(staliro_opt.taliro, staliro_mtlFormula, pred_tmp, STraj, T, LT, CLG, GRD);
                end
            otherwise
                error('S-Taliro: the metric for taliro is not defined')
        end
        
    elseif isequal(staliro_opt.taliro, 'dp_t_taliro')
        
        switch staliro_opt.taliro_metric
            case 'none'
                tmp_rob = feval(staliro_opt.taliro, staliro_mtlFormula, pred_tmp, STraj, T);
            case {'hybrid_inf','hybrid'}
                if isempty(LT) || isempty(CLG)
                    error('S-TaLiRo: The location trace or the Control Location Graph or the Guard set are empty')
                else
                    tmp_rob = feval(staliro_opt.taliro, staliro_mtlFormula, pred_tmp, STraj, T, LT, CLG);
                end
        end
        
        switch staliro_opt.dp_t_taliro_direction
            case 'past'
                tmp_rob = tmp_rob.pt;
            case 'future'
                tmp_rob = tmp_rob.ft;
            case 'both'
                tmp_rob = min(cell2mat(struct2cell(tmp_rob)));
            otherwise
                error('S-Taliro: not defined whether the dp_t_taliro_direction option is set to "past", "future" or "both"')
        end
        
    else
        error('S-Taliro: not specified whether dp_taliro or dp_t_taliro should be used')
    end
    
else
    error('S-Taliro: MTL robustness computation for these input options is not supported. Please read the help file.')
end

% Need to check whether parameter estimation is performed so we can
% check for the error condition
if ~isempty(staliro_Polarity)
    if staliro_opt.map2line == 1
        
        if isa(tmp_rob, 'hydis')
            cost = map2line(tmp_rob, staliro_opt.rob_scale);
        else
            error('S-Taliro: if map2line is used then the rebustness must be a hydis object.')
        end
        
    elseif staliro_opt.map2line == 0 && isa(tmp_rob, 'hydis')
        error('S-Taliro: for parameter estimation, if the robustness is a hydis object, then map2line must be used.')
    else
        cost = tmp_rob;
    end
    rob = cost;
else
    if staliro_opt.map2line == 1
        if isa(tmp_rob, 'hydis')
            cost = map2line(tmp_rob, staliro_opt.rob_scale);
        else
            error('S-Taliro: if map2line is used then the rebustness must be a hydis object.')
        end
    else
        cost = tmp_rob;
    end
    rob = cost;
end

% normalize the parameters before they are returned to the stochastic
% optimizer
if staliro_opt.normalization == 1
    ScaledInpArray = (inpArray(:)-staliro_inpRangeUnscaled(:,1))./(staliro_inpRangeUnscaled(:,2)-staliro_inpRangeUnscaled(:,1));
    cur_par = ScaledInpArray(end - size(staliro_ParameterIndex,2) + 1:end);
end

% handle parameter estimation
if ~isempty(staliro_Polarity)

    if rob <= 0 && staliro_opt.param_est_fals_stage == 1
        staliro_opt.param_est_fals_stage = 0;
        disp(' ')
        disp('Falsifying trajectory found on parameter boundaries.')
        disp('Continuing with Parameter Estimation method for the parameter range ...')
        disp(' ')
    end
    
    % get the range of the parameters from the predicates
    tempRng = vertcat(staliro_Predicate(staliro_ParameterIndex).range);
    
    % in case we use the normalization option, we set the right bound of the
    % range(whose norm will be used as the gamma for the optimization
    % function) to 1
    if staliro_opt.normalization == 1
        tempRng(:,2) = 1;
    end    
    
    if cost < 0
        if strcmp(staliro_opt.polarity_weight,'norm')
            cost = norm(cur_par);
        elseif strcmp(staliro_opt.polarity_weight,'max')
            cost = max(cur_par);
        elseif strcmp(staliro_opt.polarity_weight,'min')
            cost = min(cur_par);
        elseif ( size(staliro_opt.polarity_weight,2) == size(staliro_ParameterIndex,2) ) && ~any(find(staliro_opt.polarity_weight>1)) && ~any(find(staliro_opt.polarity_weight<0)) && (abs(sum(staliro_opt.polarity_weight) - 1) < 0.000001)
            cost = staliro_opt.polarity_weight * cur_par;
        else
            if isa(staliro_opt.polarity_weight, 'function_handle')
                cost = staliro_opt.polarity_weight(cur_par);
            else
                error('S-TaLiRo: option setting for polarity_weight is invalid.')
            end   
        end
        % target parameter value
        if ~isempty(staliro_opt.RobustnessOffset);
            cost = cost - staliro_opt.RobustnessOffset;
        end
        
    else
        if fcn_cmp(1, 0)
            % When the robustness is positive and the lower bound of theta negative
            % then we must make sure that max is below the lower bound of
            % theta.
            % Handle different optimization preferences for parameters 
            if strcmp(staliro_opt.polarity_weight,'norm')
                cost = norm(cur_par) - norm(tempRng(:,2)) - cost;
            elseif strcmp(staliro_opt.polarity_weight,'max')
                cost = max(cur_par) - norm(tempRng(:,2)) - cost;
            elseif strcmp(staliro_opt.polarity_weight,'min')
                cost = min(cur_par) - norm(tempRng(:,2)) - cost;
            elseif ( size(staliro_opt.polarity_weight,2) == size(staliro_ParameterIndex,2) ) && ~any(find(staliro_opt.polarity_weight>1)) && ~any(find(staliro_opt.polarity_weight<0)) && (abs(sum(staliro_opt.polarity_weight) - 1) < 0.000001)
                cost = staliro_opt.polarity_weight * cur_par - norm(tempRng(:,2)) - cost;
            else
                if isa(staliro_opt.polarity_weight, 'function_handle')
                    cost = staliro_opt.polarity_weight(cur_par) - norm(tempRng(:,2)) - cost;
                else
                    error('S-TaLiRo: option setting for polarity_weight is invalid.')
                end
            end
        else
            % we can add the upper bound of the range of the parameter in order not
            % to have the robustness value changing the min value.
            % Handle different optimization preferences for parameters
            if strcmp(staliro_opt.polarity_weight,'norm')
                cost = norm(cur_par) + norm(tempRng(:,2)) + cost;
            elseif strcmp(staliro_opt.polarity_weight,'max')
                cost = max(cur_par) + norm(tempRng(:,2)) + cost;
            elseif strcmp(staliro_opt.polarity_weight,'min')
                cost = min(cur_par) + norm(tempRng(:,2)) + cost;
            elseif ( size(staliro_opt.polarity_weight,2) == size(staliro_ParameterIndex,2) ) && ~any(find(staliro_opt.polarity_weight>1)) && ~any(find(staliro_opt.polarity_weight<0)) && (abs(sum(staliro_opt.polarity_weight) - 1) < 0.000001)
                cost = staliro_opt.polarity_weight * cur_par + norm(tempRng(:,2)) + cost;
            else
                if isa(staliro_opt.polarity_weight, 'function_handle')
                    cost = staliro_opt.polarity_weight(cur_par) + norm(tempRng(:,2)) + cost;
                else
                    error('S-TaLiRo: option setting for polarity_weight is invalid.')
                end
            end
        end
    end
end

end



