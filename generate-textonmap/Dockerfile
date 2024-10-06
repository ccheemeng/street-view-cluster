FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
RUN apt-get update && apt-get install -y python3-ipykernel

COPY PbLite-Contour-Detection/ ./PbLite-Contour-Detection/
COPY run-pblite.sh ./

EXPOSE 8004

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8004", "--no-browser", "--allow-root", "--NotebookApp.token='generate-textonmap'"]