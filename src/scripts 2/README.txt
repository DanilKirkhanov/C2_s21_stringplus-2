Инструкция по запуску Linux через Docker

1. Закинуть эти два файла в репозиторий 

1.1) Проверить, что Dockerfile так и называется, а не  Dockerfile.file Dockerfile.txt

2. Открыть Docker(Просто открыть!). Инструкция по установке Docker: https://21-school-by-students.notion.site/Docker-install-on-school-iMacs-9354ef106a8a40c6b46a69cea0a11bf8

3. В терминале запустить эти три команды:

docker-compose build

docker-compose up -d

docker exec -it ubuntu\alpine bash

4. Перейти в папку repository, там находятся все файлы

cd repository/

5. Далее следовать по пути до папки src. Можно спокойно работать в программой.
