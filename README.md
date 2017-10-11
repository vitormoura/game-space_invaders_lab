# game-space_invaders_lab
Um dos primeiros laboratórios de desenvolvimento de jogos, dessa vez utilizando o SFML para implementar um clone de Space Invaders.

### Instalação

Para compilar o projeto, efetue o [download do SFML](https://www.sfml-dev.org/tutorials/2.4/start-vc.php) e descompacte em um lugar conhecido. Em seguida, edite o arquivo `sfml2_1_vsdebug.props` para redefinir a localização onde o Visual Studio vai encontrar as bibliotecas e headers do SFML. Será necessário também copiar a dll `openal32.dll` (Fornecida junto ao download do SFML) para o diretório de execução (Geralmente a pasta `Debug`).

Por padrão, o projeto está configurado para ser compilado usando o Visual Studio 2015.