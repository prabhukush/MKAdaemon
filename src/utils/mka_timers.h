/*******************************************************************************
*
* MKA daemon.
* SPDX-FileCopyrightText: 2022 Technica Engineering GmbH <macsec@technica-engineering.de>
* SPDX-License-Identifier: GPL-2.0-or-later
* file: mka_timers.h
*
* © 2022 Technica Engineering GmbH.
*
* This program is free software: you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation, either version 2 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this program. If not, see https://www.gnu.org/licenses/
*
*******************************************************************************/

/*******************************************************************************
 * @file        mka_timers.h
 * @version     1.0.0
 * @author      Andreu Montiel
 * @brief       MKA types abstraction
 *
 * @{
 */

#ifndef MKA_TIMERS_H_
#define MKA_TIMERS_H_

/*******************        Includes        *************************/
#include "mka_private.h"

//lint -save

#ifdef __cplusplus
extern "C" {
#endif

/*******************        Defines           ***********************/
#define MKA_TIMER_MAX           0xFFFFFFFFUL

/*******************        Types             ***********************/
typedef struct {
    uint32_t expiry;
} t_mka_timer;

/*******************        Variables         ***********************/
extern uint32_t mka_tick_time_ms;

/*******************        Func. prototypes  ***********************/

/**
 * This function initialises a timer as stopped.
 *
 * @remark It is optional, and it's possible to start a timer directly in \
 *          case the initial state does not matter.
 *
 * @param[in] timer     Pointer to timer object
 */
static inline void mka_timer_init(t_mka_timer* const timer)
{
    timer->expiry = MKA_TIMER_MAX;
}

/**
 * This function starts a timer to count a given amount of time.
 *
 * @param[in] timer         Pointer to timer object
 * @param[in] how_long_ms   Amount of time to count
 */
static inline void mka_timer_start(t_mka_timer* const timer, uint32_t how_long_ms)
{
    timer->expiry = mka_tick_time_ms + how_long_ms;
}

/**
 * This function prepares the timer for the next cycle.
 *
 * @param[in] timer         Pointer to timer object
 * @param[in] how_long_ms   Amount of time to count
 */
static inline void mka_timer_extend(t_mka_timer* const timer, uint32_t how_long_ms)
{
    timer->expiry += how_long_ms;
}

/**
 * This function sets the timer to stopped state.
 *
 * @param[in] timer         Pointer to timer object
 */
static inline void mka_timer_stop(t_mka_timer* const timer)
{
    timer->expiry = MKA_TIMER_MAX;
}

/**
 * This function checks whether the timer is running (not stopped).
 *
 * @param[in] timer         Pointer to timer object
 */
static inline bool mka_timer_running(t_mka_timer const* const timer)
{
    return (MKA_TIMER_MAX > timer->expiry);
}

/**
 * This function evaluates whether a timer has expired.
 *
 * @param[in] timer         Pointer to timer object
 */
static inline bool mka_timer_expired(t_mka_timer const* const timer)
{
    return (mka_tick_time_ms >= timer->expiry);
}

/*******************        Func. definition  ***********************/

#ifdef __cplusplus
}
#endif

#endif /* MKA_TIMERS_H_ */

//lint -restore

/** @} */


