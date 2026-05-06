# АРМ сотрудника туристического агентства

## Краткое описание
GUI-приложение на Qt5 для автоматизации работы сотрудника туристического агентства: учёт направлений, туристов и путёвок, поиск, сортировка, формирование отчётов и аналитических диаграмм. Данные хранятся локально в бинарном формате `.bin`.

## Как запустить?

### Готовый дистрибутив
Поставка включает два варианта (см. `dist/` после упаковки):

1. **AppImage** (один self-contained файл):
   ```sh
   chmod +x QtProject-x86_64.AppImage
   ./QtProject-x86_64.AppImage
   ```
   Если в системе нет FUSE:
   ```sh
   ./QtProject-x86_64.AppImage --appimage-extract-and-run
   ```

2. **tar.gz-бандл** (не требует установки дополнительных пакетов, таких как FUSE:
   ```sh
   tar -xzf QtProject-linux-x86_64.tar.gz
   cd QtProject
   ./run.sh
   ```

### Сборка из исходников
1. Установите зависимости (на Debian/Ubuntu):
   ```sh
   sudo apt install build-essential cmake qtbase5-dev qttools5-dev-tools libqt5charts5-dev
   ```
2. Соберите проект:
   ```sh
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build -j$(nproc)
   ```
3. Запустите:
   ```sh
   ./build/QtProject
   ```

## Основные классы
- `DataStorage` — хранение данных БД в ОЗУ (направления, туристы, путёвки) с (де)сериализацией в `.bin` файлы.
- `MainWindow` — главное окно приложения: вкладки и кнопки загрузки/сохранения БД.
- `BaseTabWidget` — общий поведенческий шаблон вкладки (поиск, сортировка, выбор записи, кнопки).
- `BaseTableModel` — общий интерфейс табличной модели поверх `QAbstractTableModel`.
- `BaseEntryDialog` — общая шаблон диалогового окна добавления/изменения записи с валидацией ввода.
- `BaseChartDialog` — общий шаблон диалога с диаграммами.
- `DestinationTabWidget`, `TouristTabWidget`, `TouristPackageTabWidget` — реализации вкладок.
- `NewDestinationEntryDialog`, `NewTouristEntryDialog`, `NewTouristPackageEntryDialog` — реализация форм добавления/редактирования.
- `DestinationChartDialog`, `TouristChartDialog`, `TouristPackageChartDialog` — реализация форм диаграмм.
- `ReportDialog` — диалоговое окно отображения и сохранения текстовых отчётов.
- `EntrySelectionDialog` — диалоговое окно выбора одной/нескольких записей из таблицы.
- `SoftRegexValidator` — валидатор текстового ввода.

## Лицензия
MIT © 2026 Кучер Юлиан, Васильев Андрей
