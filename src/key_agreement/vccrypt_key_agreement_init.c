/**
 * \file vccrypt_key_agreement_init.c
 *
 * Initialize a key agreement instance from an options structure.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <string.h>
#include <vccrypt/key_agreement.h>
#include <vpr/abstract_factory.h>
#include <vpr/parameters.h>

/* forward decls */
static void vccrypt_key_agreement_dispose(void* context);

/**
 * Initialize a key agreement algorithm instance with the given options.
 *
 * If initialization is successful, then this key agreement algorithm
 * instance is owned by the caller and must be disposed by calling dispose()
 * when no longer needed.
 *
 * \param options       The options to use for this algorithm instance.
 * \param context       The key agreement algorithm instance to initialize.
 *
 * \returns 0 on success and non-zero on failure.
 */
int vccrypt_key_agreement_init(
    vccrypt_key_agreement_options_t* options,
    vccrypt_key_agreement_context_t* context)
{
    MODEL_ASSERT(options != NULL);
    MODEL_ASSERT(options->vccrypt_key_agreement_alg_init != NULL);
    MODEL_ASSERT(options->vccrypt_key_agreement_alg_dispose != NULL);
    MODEL_ASSERT(context != NULL);

    if (options == NULL || options->vccrypt_key_agreement_alg_init == NULL ||
        options->vccrypt_key_agreement_alg_dispose == NULL ||
        context == NULL)
    {
        return 1;
    }

    memset(context, 0, sizeof(vccrypt_key_agreement_context_t));
    context->hdr.dispose = &vccrypt_key_agreement_dispose;
    context->options = options;

    return options->vccrypt_key_agreement_alg_init(options, context);
}

/**
 * Dispose of a key agreement instance.
 *
 * \param context           The opaque pointer to this instance.
 */
static void vccrypt_key_agreement_dispose(void* context)
{
    vccrypt_key_agreement_context_t* ctx =
        (vccrypt_key_agreement_context_t*)context;

    MODEL_ASSERT(ctx != NULL);
    MODEL_ASSERT(ctx->options != NULL);
    MODEL_ASSERT(ctx->options->vccrypt_key_agreement_alg_dispose != NULL);

    /* perform the algorithm-specific disposal */
    ctx->options->vccrypt_key_agreement_alg_dispose(ctx->options, ctx);

    /* clear out the structure */
    memset(ctx, 0, sizeof(vccrypt_key_agreement_context_t));
}