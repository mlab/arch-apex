#ifndef _LCM_EVENTLOG_H_
#define _LCM_EVENTLOG_H_

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WIN64)
  #if defined(lcm_EXPORTS)
    #define LCM_API_FUNCTION __declspec( dllexport )
  #else
    #define LCM_API_FUNCTION __declspec( dllimport )
  #endif
#else
  #define LCM_API_FUNCTION
#endif

/**
 * @defgroup LcmC_lcm_eventlog_t lcm_eventlog_t
 * @ingroup LcmC
 * @brief Read and write %LCM log files
 *
 * <tt> #include <lcm/lcm.h> </tt>
 *
 * Linking: <tt> `pkg-config --libs lcm` </tt>
 *
 * @{
 */

typedef struct _lcm_eventlog_t lcm_eventlog_t;
struct _lcm_eventlog_t
{
    /**
     * The underlying file handle.  Use this at your own risk.  Example use
     * cases include implementing your own seek routine for read-mode logs, or
     * rewinding the file pointer to the beginning of the log file.
     */
    FILE *f;
    /**
     * Do not use.
     */
    int64_t eventcount;
};

/**
 * Represents a single event (message) in a log file.
 */
typedef struct _lcm_eventlog_event_t lcm_eventlog_event_t;
struct _lcm_eventlog_event_t {
    /**
     * A monotonically increasing number assigned to the message to identify it
     * in the log file.
     */
    int64_t eventnum;
    /**
     * Time that the message was received, in microseconds since the UNIX
     * epoch
     */
    int64_t timestamp;
    /**
     * Length of @c channel, in bytes
     */
    int32_t channellen;
    /**
     * Length of @c data, in bytes
     */
    int32_t datalen;

    /**
     * Channel that the message was received on
     */
    char     *channel;
    /**
     * Raw byte buffer containing the message payload.
     */
    void     *data;
};

/**
 * Open a log file for reading or writing.
 *
 * @param path Log file to open
 * @param mode "r" (read mode) or "w" (write mode)
 *
 * @return a newly allocated lcm_eventlog_t, or NULL on failure.
 */
LCM_API_FUNCTION
lcm_eventlog_t *lcm_eventlog_create(const char *path, const char *mode);

/**
 * Read the next event in the log file.  Valid in read mode only.  Free the
 * returned structure with lcm_eventlog_free_event() after use.
 *
 * @param eventlog The log file object
 *
 * @return the next event in the log file, or NULL when the end of the file has
 * been reached.
 */
LCM_API_FUNCTION
lcm_eventlog_event_t *lcm_eventlog_read_next_event(lcm_eventlog_t *eventlog);

/**
 * Free a structure returned by lcm_eventlog_read_next_event().
 *
 * @param event A structure returned by lcm_eventlog_read_next_event()
 */
LCM_API_FUNCTION
void lcm_eventlog_free_event(lcm_eventlog_event_t *event);

/**
 * Seek (approximately) to a particular timestamp.
 *
 * @param eventlog The log file object
 * @param ts Timestamp of the target event in the log file.
 *
 * @return 0 on success, -1 on failure
 */
LCM_API_FUNCTION
int lcm_eventlog_seek_to_timestamp(lcm_eventlog_t *eventlog, int64_t ts);

/**
 * Write an event into a log file.  Valid in write mode only.
 *
 * @param eventlog The log file object
 * @param event The event to write to the file.  On return, the eventnum field
 * will be filled in for you.
 *
 * @return 0 on success, -1 on failure.
 */
LCM_API_FUNCTION
int lcm_eventlog_write_event(lcm_eventlog_t *eventlog,
        lcm_eventlog_event_t *event);

/**
 * Close a log file and release allocated resources.
 *
 * @param eventlog The log file object
 */
LCM_API_FUNCTION
void lcm_eventlog_destroy(lcm_eventlog_t *eventlog);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
