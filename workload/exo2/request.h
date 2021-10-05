#ifndef _REQUEST_H_
#define _REQUEST_H_

#define ALIGNED 64
#define PI 3.14

typedef unsigned long long u64;

typedef struct request_s
{
  u64 n;
  u64 *estampille;
  u64 *start;
  u64 *type;       // read=0 and write=1
  u64 *address;
  u64 *size;
} request_t;

u64 *gen_estampille(u64 n);

u64 *gen_start_seq(u64 n, u64 t_0, u64 t);
u64 *gen_start_uniform(u64 n, u64 t_min, u64 t_max);

u64 *gen_type_seq(u64 n, u64 p);
u64 *gen_type_unifrom(u64 n, u64 n_r, u64 n_w);

u64 *gen_addr_seq(u64 n, u64 a, u64 s);
u64 *gen_addr_uniform(u64 n, u64 a_min, u64 a_max);
u64 *gen_addr_random(u64 n, u64 h, u64 p_h, u64 c);

u64 *gen_size_seq(u64 n, u64 s);
u64 *gen_size_uniform(u64 n, u64 s_min, u64 s_max);
u64 *gen_size_normal(u64 n, u64 s_mean, u64 s_var);

request_t *gen_request(config_t *config);
void print_request(char *filename, request_t *r);
void free_request(request_t *r);

#endif // _REQUEST_H_
