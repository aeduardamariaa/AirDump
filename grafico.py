import datetime
import json
import requests
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl


def get_request(url, proxy, auth):
    req = requests.get(url, proxies =proxy, auth=auth)

    if req.status_code != 200:
        raise Exception('Erro de autenticação')

    return req.content


url = "https://iiot-dta-default-rtdb.firebaseio.com/avaliacao/subsys_05.json"

proxy = {
    "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080",
    "https":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"
}

auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

def update_data():
    dados = json.loads(get_request(url, proxy, auth)) #carrega dados em json
    dados_len = len(dados)

    media = np.full(dados_len, np.nan, dtype=np.float64)
    desvio = np.full(dados_len, np.nan, dtype=np.float64)

    for i, j in zip(range(dados_len)): #não poderia ser dois FOR
        try:
            media[i] = dados["media"]
            desvio[i] = dados["desvio"]
        except KeyError:
            pass

    media_mean = np.mean(media[~np.isnan(media)])
    desvio_mean = np.mean(desvio[~np.isnan(desvio)])

    return media_mean, desvio_mean

fig, axs = plt.subplots(2, sharex=True, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #retorna o grafico e os eixos
fig.supxlabel("Tempo")
ax_media_mean, ax_desvio_mean = axs

cmap = mpl.colormaps["coolwarm"]

ax_media_mean.grid(True)
ax_media_mean.set_ylabel("Media")

ax_desvio_mean.grid(True)
ax_desvio_mean.set_ylabel("Desvio Padrão")


plt.ion()
fig.show()
fig.canvas.draw()

while True:
    media_mean, desvio_mean = update_data()
    tempo_atual = datetime.datetime.now()

    temp_color_00 = (media_mean - 30)/(35-25)


    ax_media_mean.plot(tempo_atual, ax_media_mean, linestyle='', marker='o', markersize=5, color='r')
    ax_desvio_mean.plot(tempo_atual, ax_desvio_mean, linestyle='', marker='o', markersize=5, color=cmap(temp_color_00))

    fig.canvas.draw()
    plt.pause(3)