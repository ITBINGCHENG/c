port: 7890
socks-port: 7891
allow-lan: false
mode: Rule
log-level: info
external-controller: 127.0.0.1:9090
experimental:
  ignore-resolve-fail: true
hosts:
  mtalk.google.com: 108.177.125.188
proxies:
  - name: ss
    type: ss
    server: server
    port: 443
    cipher: chacha20-ietf-poly1305
    password: password
    _index: 0
  - name: ss-obfs
    type: ss
    server: server
    port: 443
    cipher: chacha20-ietf-poly1305
    password: password
    plugin: obfs
    plugin-opts:
      mode: tls
      host: example.com
  - name: ss-v2ray
    type: ss
    server: server
    port: 443
    cipher: chacha20-ietf-poly1305
    password: password
    plugin: v2ray-plugin
    plugin-opts:
      mode: websocket
  - name: v2ray
    type: vmess
    server: changanyue.ml
    port: 443
    uuid: 847faca9-7f61-4e88-bcf8-22ac9b62a3da
    alterId: 0
    cipher: auto
    udp: true
    tls: true
    skip-cert-verify: true
    network: ws
    ws-opts:
      path: /
  - name: trojan
    type: trojan
    server: server
    port: 443
    password: password
    alpn:
      - h2
      - http/1.1
proxy-groups:
  - name: 自动选择快速节点
    type: url-test
    proxies:
      - v2ray
      - ss-v2ray
      - ss
      - ss-obfs
      - trojan
    url: http://www.gstatic.com/generate_204
    interval: 300
  - name: PROXY
    type: select
    proxies:
      - 自动选择快速节点
      - ss
      - ss-obfs
      - ss-v2ray
      - v2ray
      - trojan
  - name: Final
    type: select
    proxies:
      - DIRECT
      - PROXY
  - name: Apple
    type: select
    proxies:
      - DIRECT
      - PROXY
  - name: GlobalMedia
    type: select
    proxies:
      - PROXY
      - ss
      - ss-obfs
      - ss-v2ray
      - v2ray
      - trojan
  - name: HKMTMedia
    type: select
    proxies:
      - DIRECT
      - ss
      - ss-obfs
      - ss-v2ray
      - v2ray
      - trojan
rule-providers:
  reject:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/reject.txt
    path: ./ruleset/reject.yaml
    interval: 86400
  icloud:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/icloud.txt
    path: ./ruleset/icloud.yaml
    interval: 86400
  apple:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/apple.txt
    path: ./ruleset/apple.yaml
    interval: 86400
  google:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/google.txt
    path: ./ruleset/google.yaml
    interval: 86400
  proxy:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/proxy.txt
    path: ./ruleset/proxy.yaml
    interval: 86400
  direct:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/direct.txt
    path: ./ruleset/direct.yaml
    interval: 86400
  private:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/private.txt
    path: ./ruleset/private.yaml
    interval: 86400
  gfw:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/gfw.txt
    path: ./ruleset/gfw.yaml
    interval: 86400
  greatfire:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/greatfire.txt
    path: ./ruleset/greatfire.yaml
    interval: 86400
  tld-not-cn:
    type: http
    behavior: domain
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/tld-not-cn.txt
    path: ./ruleset/tld-not-cn.yaml
    interval: 86400
  telegramcidr:
    type: http
    behavior: ipcidr
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/telegramcidr.txt
    path: ./ruleset/telegramcidr.yaml
    interval: 86400
  cncidr:
    type: http
    behavior: ipcidr
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/cncidr.txt
    path: ./ruleset/cncidr.yaml
    interval: 86400
  lancidr:
    type: http
    behavior: ipcidr
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/lancidr.txt
    path: ./ruleset/lancidr.yaml
    interval: 86400
  applications:
    type: http
    behavior: classical
    url: https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/applications.txt
    path: ./ruleset/applications.yaml
    interval: 86400
rules:
  - RULE-SET,applications,DIRECT
  - DOMAIN,clash.razord.top,DIRECT
  - DOMAIN,yacd.haishan.me,DIRECT
  - RULE-SET,private,DIRECT
  - RULE-SET,reject,REJECT
  - RULE-SET,icloud,DIRECT
  - RULE-SET,apple,DIRECT
  - RULE-SET,google,PROXY
  - RULE-SET,proxy,PROXY
  - RULE-SET,direct,DIRECT
  - RULE-SET,lancidr,DIRECT
  - RULE-SET,cncidr,DIRECT
  - RULE-SET,telegramcidr,PROXY
  - GEOIP,LAN,DIRECT
  - GEOIP,CN,DIRECT
  - MATCH,PROXY
cfw-bypass:
  - qq.com
  - music.163.com
  - "*.music.126.net"
  - localhost
  - 127.*
  - 10.*
  - 172.16.*
  - 172.17.*
  - 172.18.*
  - 172.19.*
  - 172.20.*
  - 172.21.*
  - 172.22.*
  - 172.23.*
  - 172.24.*
  - 172.25.*
  - 172.26.*
  - 172.27.*
  - 172.28.*
  - 172.29.*
  - 172.30.*
  - 172.31.*
  - 192.168.*
  - <local>
cfw-latency-timeout: 5000
