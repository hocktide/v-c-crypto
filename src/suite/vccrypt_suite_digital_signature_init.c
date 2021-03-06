/**
 * \file vccrypt_suite_digital_signature_init.c
 *
 * Initialize a digital signature instance for this crypto suite.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <string.h>
#include <vccrypt/suite.h>
#include <vpr/abstract_factory.h>
#include <vpr/parameters.h>

/**
 * \brief Create an appropriate digital signature algorithm instance for this
 * crypto suite.
 *
 * \param options       The options structure for this crypto suite.
 * \param context       The digital signature instance to initialize.
 *
 * \returns a status indicating success or failure.
 *      - \ref VCCRYPT_STATUS_SUCCESS on success.
 *      - a non-zero return code on failure.
 */
int vccrypt_suite_digital_signature_init(
    vccrypt_suite_options_t* options,
    vccrypt_digital_signature_context_t* context)
{
    MODEL_ASSERT(context != NULL);
    MODEL_ASSERT(options != NULL);
    MODEL_ASSERT(options->vccrypt_suite_digital_signature_alg_init != NULL);

    return options->vccrypt_suite_digital_signature_alg_init(options, context);
}
