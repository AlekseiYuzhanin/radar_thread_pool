# Уровень 2 Кейс 9
## Описание:
Пул потоков

Цель проекта: получения информации о навыках кандидата по разработке многопоточных приложений.

Исходные данные, условия, ограничения:

разработать класс, реализующий работу пула потоков, в котором необходимо:

реализовать конструктор, в который передается количество рабочих потоков;

метод, запускающий работу потоков (init);

метод, ожидающий выполнения всех рабочих потоков и закрывающий работу пула потоков;

метод, отправляющий функцию для асинхронного выполнения пулом потоков;

Требования к конечному результату:

для реализации пула потоков желательно использовать потокобезопасную очередь, реализованную ранее;

в классе должны быть удалены конструкторы копирования, перемещения, а также перемещающий и копирующий
операторы присваивания;

допустимо использовать стандарты языка С++ 11 или C++ 14.

# Инструкция запуска :
## G++ :
Необходимое ПО: компилятор g++, git.
```console
example@user:~/$ git clone https://github.com/AlekseiYuzhanin/radar_thread_pool
example@user:~/$ cd radar_thread_pool
example@user:~/radar_thread_pool$ g++ main.cpp -o <название_проекта>
example@user:~/radar_thread_pool$.<название_проекта>
```
## Make :
Необходимое ПО: компилятор gcc, компилятор g++, make, git.
```console
example@user:~/$ git clone https://github.com/AlekseiYuzhanin/radar_thread_pool
example@user:~/$ cd radar_thread_pool
example@user:~/radar_thread_pool$ make build
example@user:~/radar_thread_pool$ make start
```
## Docker :
Необходимое ПО: Docker, git.
```console
example@user:~/$ git clone https://github.com/AlekseiYuzhanin/radar_thread_pool
example@user:~/$ cd radar_thread_pool
example@user:~/radar_thread_pool$ docker build -t <название_проекта> .
example@user:~/radar_thread_pool$ docker run <название_проекта>ю
```
