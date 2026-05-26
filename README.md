# eBPF Latency Tracer para Redes Financeiras

Rastreia RTT de pacotes em conexões de bolsa no kernel Linux — sem overhead de user-space tradicional.

## Stack

- C (eBPF), BCC/libbpf
- Python (orquestração)
- Grafana

## Diagrama — interceptação no kernel

```
 NIC ──► kernel network stack
              │
         [eBPF kprobe/tracepoint]
              │  ts ingress / egress
              ▼
         BPF map (per-flow histogram)
              │
         user-space exporter ──► Prometheus ──► Grafana (µs)
```

Detalhes: [docs/SYSCALL_FLOW.md](docs/SYSCALL_FLOW.md)

## Injeção segura

- Requer `CAP_BPF` / root para carregar programa
- Validar com `bpftool prog show`
- Usar CO-RE (Compile Once — Run Everywhere) quando possível
- Ver [docs/SAFE_LOADING.md](docs/SAFE_LOADING.md)

## Quick start

```bash
sudo python3 tools/load_tracer.py --iface eth0 --port 443
docker compose up -d  # Grafana + Prometheus
```

Painéis: latência p50/p99/p999 em **microssegundos** por fluxo (src:dst:port).

## Estrutura

| Pasta | Função |
|-------|--------|
| `bpf/` | Programas eBPF |
| `tools/` | Loader Python |
| `grafana/` | Dashboards |
| `exporter/` | Métricas Prometheus |
