/**
 * \file vccrypt_mac_finalize.c
 *
 * Finalize the mac and write the authentication code to the output buffer.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <string.h>
#include <vccrypt/mac.h>
#include <vpr/abstract_factory.h>
#include <vpr/parameters.h>

/**
 * \brief Finalize the message authentication code, copying the output data to
 * the given buffer.
 *
 * \param context       The MAC instance.
 * \param mac_buffer    The buffer to receive the MAC.  Must be large enough for
 *                      the given MAC algorithm.
 *
 * \returns a status indicating success or failure.
 *      - \ref VCCRYPT_STATUS_SUCCESS on success.
 *      - \ref VCCRYPT_ERROR_MAC_FINALIZE_INVALID_ARG if an invalid argument is
 *             provided.
 *      - a non-zero return code on error.
 */
int vccrypt_mac_finalize(
    vccrypt_mac_context_t* context, vccrypt_buffer_t* mac_buffer)
{
    MODEL_ASSERT(context != NULL);
    MODEL_ASSERT(context->options != NULL);
    MODEL_ASSERT(context->options->mac_size > 0);
    MODEL_ASSERT(context->options->vccrypt_mac_alg_finalize != NULL);
    MODEL_ASSERT(mac_buffer != NULL);
    MODEL_ASSERT(mac_buffer->data != NULL);
    MODEL_ASSERT(mac_buffer->size >= context->options->mac_size);

    /* sanity check on parameters */
    if (context == NULL || context->options == NULL ||
        context->options->vccrypt_mac_alg_finalize == NULL ||
        mac_buffer == NULL || mac_buffer->data == NULL ||
        mac_buffer->size < context->options->mac_size)
    {
        return VCCRYPT_ERROR_MAC_FINALIZE_INVALID_ARG;
    }

    return context->options->vccrypt_mac_alg_finalize(context, mac_buffer);
}
