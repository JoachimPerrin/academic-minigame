docker-compose up --build game-devel
docker exec -it game_cpp-game-devel-1 bash
valgrind --leak-check=yes ./Game