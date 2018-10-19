ARG BASE_IMAGE_VERSION
FROM corba-base-builder:${BASE_IMAGE_VERSION} as builder

COPY src /usr/src/corba_perf

WORKDIR /usr/src/corba_perf

RUN cmake3 . \
    && \
    make

FROM corba-base-runner:${BASE_IMAGE_VERSION}

COPY --from=builder /usr/src/corba_perf/corba_perf /usr/local/sbin/corba_perf

ENV IOR_INPUT_FILE server.ior
ENV CALL_COUNT 1
ENV ORB_ARGS ""
ENV METHOD_NAME ""
ENV METHOD_ARGS ""
ENV METHOD_TYPS ""

ENTRYPOINT /usr/local/sbin/corba_perf \
              -r $(cat /ior-volume/${IOR_INPUT_FILE}) -i ${CALL_COUNT} -n ${METHOD_NAME} -a ${METHOD_ARGS} -t ${METHOD_TYPS} \
              ${ORB_ARGS}
