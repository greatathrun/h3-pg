/*
 * Copyright 2018 Bytes & Brains
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PGH3_H
#define PGH3_H

#include <h3/h3api.h> // Main H3 include

typedef struct
{
    H3Index *indices;
    int *distances;
} hexDistanceTuple;

/* base type in postgres is Datum, and we cannot fit 8 bytes on all platforms
   so we use pointers */
#define PG_RETURN_H3_INDEX_P(x) PG_RETURN_POINTER(x)
#define PG_GETARG_H3_INDEX_P(x) (H3Index *)PG_GETARG_POINTER(x)

Datum srf_return_h3_indexes_from_user_fctx(PG_FUNCTION_ARGS);
Datum srf_return_h3_index_distances_from_user_fctx(PG_FUNCTION_ARGS);

#define SRF_RETURN_H3_INDEXES_FROM_USER_FCTX() \
    return srf_return_h3_indexes_from_user_fctx(fcinfo)

#define SRF_RETURN_H3_INDEX_DISTANCES_FROM_USER_FCTX() \
    return srf_return_h3_index_distances_from_user_fctx(fcinfo)

#define ENSURE_TYPEFUNC_COMPOSITE(x)                                               \
    if (x != TYPEFUNC_COMPOSITE)                                                   \
    {                                                                              \
        ereport(ERROR,                                                             \
                (errcode(ERRCODE_INVALID_PARAMETER_VALUE),                         \
                 errmsg("Function returning record called in context that cannot " \
                        "accept type record")));                                   \
    }

#endif