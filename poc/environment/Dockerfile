FROM ubuntu:22.04@sha256:3b06811b2afd352be909dd088a004166d665dc76d38b13eada33522a9d915c6f

RUN apt-get update && apt-get install -y \
gcc-11=11.4.0-1ubuntu1~22.04.3 \
make \
curl \
xz-utils \
tmux \
python3 \
python3-pip \
nano \
file \
&& pip install pwntools \
&& curl --proto '=https' --tlsv1.2 -LsSf 'https://install.pwndbg.re' | sh -s -- -t pwndbg-gdb

WORKDIR /poc/

CMD [ "/bin/bash" ]
