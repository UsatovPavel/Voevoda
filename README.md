# Voevoda

![logo](https://i.pinimg.com/originals/7a/3d/c5/7a3dc534690705532b86dd9b542311ad.png)

## Описание
Одиночная игра с видом сверху в жанре RTS. Игрок управляет генералом на 2D карте, может сражаться с другими генералами-ботами и пополять армию в городах.

В главном меню во вкладке **settings** игрок может создать аккаунт, или войти в существующий.

![menu_login](https://i.pinimg.com/originals/dc/dc/82/dcdc829e372170a076ff80c374efa2d4.png)
 
## Запуск проекта: 
- Скачать **[Unreal engine](https://www.unrealengine.com/en-US)**
- Скачать версию движка **4.27**
- Создать проект с именем **Voevoda** и скопировать в него файлы из ветки **main**
- Компиляция: обновить **Sourse/Voevoda.Build.cs** - библиотеки подгрузятся.
- Проставить в Blueprint классы для Strategist, PlayerCharacter, GameWorld.
- Обновить Blueprint-схемы
- Запустить сервер
  - перейти в **httpServer**
  - запустить **./main** через консоль
