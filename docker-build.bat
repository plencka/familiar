@echo off
docker-compose build || goto :error
docker create --name familiar_tmp familiar_app
rmdir -r builds /s /q
docker cp familiar_tmp:/application/builds ./
docker rm familiar_tmp
exit
:error
pause