/**
 * \file vccrypt_suite_buffer_init_for_hash.c
 *
 * Initialize a crypto buffer sized appropriately for suite hash operations.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <string.h>
#include <vccrypt/suite.h>
#include <vpr/abstract_factory.h>
#include <vpr/parameters.h>

/**
 * \brief Create a buffer sized appropriately for the output of this crypto
 * suite's hash algorithm.
 *
 * \param options       The options structure for this crypto suite.
 * \param buffer        The buffer to instance initialize.
 *
 * \returns a status indicating success or failure.
 *      - \ref VCCRYPT_STATUS_SUCCESS on success.
 *      - a non-zero return code on failure.
 */
int vccrypt_suite_buffer_init_for_hash(
    vccrypt_suite_options_t* options,
    vccrypt_buffer_t* buffer)
{
    MODEL_ASSERT(buffer != NULL);
    MODEL_ASSERT(options != NULL);
    MODEL_ASSERT(options->alloc_opts != 0);
    MODEL_ASSERT(options->hash_opts.hash_size > 0);

    return vccrypt_buffer_init(
        buffer, options->alloc_opts, options->hash_opts.hash_size);
}
