# drogon kafka

an example of using kafka with drogon framework,

consume topic using websocket & leveraging thread in drogon loop event framework.

[quick preview](https://youtu.be/mJvyoLWEgGM)
[![](https://img.youtube.com/vi/mJvyoLWEgGM/hqdefault.jpg)](https://www.youtube.com/watch?v=mJvyoLWEgGM)

<br>

---

## required library

- [lz4](https://github.com/lz4/lz4)
- [rdkafka](https://github.com/confluentinc/librdkafka)
- [cppkafka](https://github.com/mfontanini/cppkafka)
- [drogon-framework](https://github.com/drogonframework/drogon)

<br>

---

## build the example

after the required library installed, use below scrip to configure & build

> you may adjust your configuration as you need

```sh
set -e;

mkdir -p build bin logs public out;

cmake -S . -G "Ninja" -B build \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_STANDARD=17 \
      -DCMAKE_CXX_FLAGS="-std=c++17" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1;

ln -sf build/compile_commands.json ./;

cmake --build build;
```

<br>

---

### run the example

1. run your kafka server using docker or systemd

2. configure & build the project

3. go to `out` dir configured & build

4. run `producer_ctl` & `backend_drogon_kafka`

5. use websocket request with [wscat](https://github.com/websockets/wscat)
```sh
wscat -c "http://localhost:9000/ws/stock/trade"
```

<br>

__*NOTE:*__
- there's no interaction for end-user
- they only consume what publish by "kafka producer"
- data is using stock trade simulation depend on ratio

<br>

---

##### references

- [rdkafka cpp](https://developer.confluent.io/get-started/c/?session_ref=direct&url_ref=https%3A%2F%2Fdocs.confluent.io%2Fkafka-clients%2Flibrdkafka%2Fcurrent%2Foverview.html#introduction)
- [kafka config](https://kafka.apache.org/documentation/#configuration)
- [cppkafka example](https://github.com/mfontanini/cppkafka/tree/master/examples)
- [drogon websocket](https://drogonframework.github.io/drogon-docs/#/ENG/ENG-04-3-Controller-WebSocketController)
- [docker container kafka helper](https://github.com/prothegee/system-monitor-container/tree/main/service/kafka)

<br>

---

###### end of readme

