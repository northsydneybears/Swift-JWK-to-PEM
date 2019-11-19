#ifndef C_JWKPEM_OPENSSL_H
#define C_JWKPEM_OPENSSL_H

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/md4.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/pkcs12.h>
#include <openssl/x509v3.h>

EVP_MD_CTX *JWKPEM_EVP_MD_CTX_new(void);
void JWKPEM_EVP_MD_CTX_free(EVP_MD_CTX *ctx);
int JWKPEM_RSA_set0_key(RSA *r, BIGNUM *n, BIGNUM *e, BIGNUM *d);
HMAC_CTX *JWKPEM_HMAC_CTX_new(void);
void JWKPEM_HMAC_CTX_free(HMAC_CTX *ctx);

// This wrapper allows for a common call for both versions of OpenSSL when setting other keys for RSA.
static inline void JWKPEM_RSA_set_keys(RSA *rsakey, BIGNUM *n, BIGNUM *e, BIGNUM *d, BIGNUM *p, BIGNUM *q, BIGNUM *dmp1, BIGNUM *dmq1, BIGNUM *iqmp) {

    #if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
        JWKPEM_RSA_set0_key(rsakey, n, e, d);
        RSA_set0_factors(rsakey, p, q);
        RSA_set0_crt_params(rsakey, dmp1, dmq1, iqmp);
    #else
        rsakey->n = n;
        rsakey->e = e;
        rsakey->d = d;
        rsakey->p = p;
        rsakey->q = q;
        rsakey->dmp1 = dmp1;
        rsakey->dmq1 = dmq1;
        rsakey->iqmp = iqmp;
    #endif
}

static inline void JWKPEM_EVP_PKEY_assign_wrapper(EVP_PKEY *pkey, RSA *rsakey) {

    EVP_PKEY_assign(pkey, EVP_PKEY_RSA, rsakey);
}


#endif
