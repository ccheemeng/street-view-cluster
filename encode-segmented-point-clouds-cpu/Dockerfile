FROM python:3.11.10-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu && pip install --no-cache-dir -r requirements.txt &&\
    apt-get update && apt-get install -y python3-ipykernel &&\
    git clone https://github.com/HuguesTHOMAS/KPConv-PyTorch.git &&\
    cp -r ./KPConv-PyTorch/cpp_wrappers ./ &&\
    cp -r ./KPConv-PyTorch/datasets ./ &&\
    cp -r ./KPConv-PyTorch/kernels ./ &&\
    cp -r ./KPConv-PyTorch/models ./ &&\
    cp -r ./KPConv-PyTorch/utils ./ &&\
    rm -rf ./KPConv-PyTorch

WORKDIR /app/cpp_wrappers
RUN sh compile_wrappers.sh
WORKDIR /app

EXPOSE 8013

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8013", "--no-browser", "--allow-root", "--NotebookApp.token='encode-segmented-point-clouds-cpu'"]