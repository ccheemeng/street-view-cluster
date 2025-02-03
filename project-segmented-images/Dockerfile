FROM python:3.12.8-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN apt-get update && apt-get install -y python3-ipykernel
RUN pip install --no-cache-dir -r requirements.txt

EXPOSE 8019:8019

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8019", "--no-browser", "--allow-root", "--NotebookApp.token='project-segmented-images'"]