# Fluxo de syscalls e tracepoints

## Onde medir

| Hook | Evento |
|------|--------|
| `tracepoint/syscalls/sys_enter_sendto` | Saída user→kernel |
| `tracepoint/syscalls/sys_exit_recvfrom` | Retorno recv |
| `kprobe/tcp_rcv_established` | ACK recebido |

## Por que kernel

Evita context switches e cópias para user-space a cada pacote — histogramas agregados no mapa BPF.

## Grafana

Painel `latency_us` com buckets: 1, 5, 10, 50, 100, 500 µs.
