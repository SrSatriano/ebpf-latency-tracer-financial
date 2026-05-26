#!/usr/bin/env python3
"""Carrega tracer eBPF com validações de segurança."""

import argparse
import os
import sys


def main() -> int:
    parser = argparse.ArgumentParser(description="eBPF financial latency tracer")
    parser.add_argument("--iface", required=True)
    parser.add_argument("--port", type=int, default=443)
    args = parser.parse_args()

    if os.geteuid() != 0:
        print("Requer root ou CAP_BPF para carregar programas eBPF", file=sys.stderr)
        return 1

    print(f"Loading tracer on {args.iface} port {args.port}")
    print("Use libbpf/bcc to attach bpf/net_latency.c to tracepoints")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
