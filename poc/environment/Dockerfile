FROM ubuntu:22.04@sha256:3b06811b2afd352be909dd088a004166d665dc76d38b13eada33522a9d915c6f

RUN apt-get update && apt-get install -y \
gcc-11=11.4.0-1ubuntu1~22.04.3 \
make \
python3 \
python3-pip \
file \
git \
tmux \
&& pip install pwntools \
&& git clone https://github.com/pwndbg/pwndbg \
&& cd pwndbg \
&& ./setup.sh

WORKDIR /poc/

CMD [ "/bin/bash" ]
