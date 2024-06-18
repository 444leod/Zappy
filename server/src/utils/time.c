/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** timeval
*/

#include <time.h>
#include <sys/time.h>

/**
 * @brief Get the actual time
 * @details Get the actual time
 *
 * @return struct timespec The actual time
 */
struct timespec get_actual_time(void)
{
    struct timespec time;

    clock_gettime(CLOCK_REALTIME, &time);
    return (time);
}

/**
 * @brief Update the remaining time by substracting the elapsed time
 *  since the last update
 * @details Update the remaining time by substracting the elapsed time
 * since the last update
 *
 * @param remaining_time The remaining time pointer to update
 * @param last_update The last update time pointer
 */
void update_remaining_time(double *remaining_time,
    struct timespec *last_update)
{
    struct timespec actual_time = get_actual_time();
    double elapsed_time;

    elapsed_time = (actual_time.tv_sec - (*last_update).tv_sec);
    elapsed_time += (actual_time.tv_nsec -
        (*last_update).tv_nsec) / 1000000000.0;
    *remaining_time -= elapsed_time;
    *last_update = actual_time;
}

/**
 * @brief Get the timeval by a double
 * @details Get the timeval by a double
 *
 * @param wait_duration the double to convert to timeval
 *
 * @return struct timeval the timeval
 */
struct timeval get_timeval_by_double(double wait_duration)
{
    struct timeval timeout;

    timeout.tv_sec = (time_t)wait_duration;
    timeout.tv_usec = (suseconds_t)((wait_duration - timeout.tv_sec) * 1e6);
    return timeout;
}

/**
 * @brief Compare two timeval
 * @details Compare two timeval
 *
 * @param a the first timeval
 * @param b the second timeval
 *
 * @return int the result of the comparison
 */
int timevalcmp(struct timeval *a, struct timeval *b)
{
    if (a->tv_sec == b->tv_sec)
        return a->tv_usec - b->tv_usec;
    return a->tv_sec - b->tv_sec;
}
