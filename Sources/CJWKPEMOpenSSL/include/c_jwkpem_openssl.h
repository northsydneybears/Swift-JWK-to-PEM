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

//#if (OPENSSL_VERSION_NUMBER < 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
//EVP_MD_CTX *EVP_MD_CTX_new(void);
//void EVP_MD_CTX_free(EVP_MD_CTX *ctx);
//int RSA_set0_key(RSA *r, BIGNUM *n, BIGNUM *e, BIGNUM *d);
//HMAC_CTX *HMAC_CTX_new(void);
//void HMAC_CTX_free(HMAC_CTX *ctx);
//#endif

// This wrapper allows for a common call for both versions of OpenSSL when setting other keys for RSA.
static inline void RSA_set_keys(RSA *rsakey, BIGNUM *n, BIGNUM *e, BIGNUM *d, BIGNUM *p, BIGNUM *q, BIGNUM *dmp1, BIGNUM *dmq1, BIGNUM *iqmp) {

    #if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
        RSA_set0_key(rsakey, n, e, d);
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

static inline void EVP_PKEY_assign_wrapper(EVP_PKEY *pkey, RSA *rsakey) {

    EVP_PKEY_assign(pkey, EVP_PKEY_RSA, rsakey);
}


#endif
