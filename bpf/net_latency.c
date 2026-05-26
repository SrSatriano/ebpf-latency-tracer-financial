// SPDX-License-Identifier: GPL-2.0
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

struct flow_key {
  __u32 saddr;
  __u32 daddr;
  __u16 sport;
  __u16 dport;
};

struct {
  __uint(type, BPF_MAP_TYPE_HASH);
  __uint(max_entries, 65536);
  __type(key, struct flow_key);
  __type(value, __u64);
} ingress_ts SEC(".maps");

struct {
  __uint(type, BPF_MAP_TYPE_HASH);
  __uint(max_entries, 65536);
  __type(key, struct flow_key);
  __type(value, __u64);
} latency_hist SEC(".maps");

// Scaffold: anexar a tracepoints reais (tcp_probe, etc.) em produção
char LICENSE[] SEC("license") = "GPL";
