# Завдання 3 — Декодуйте backtrace

## Налаштування PlatformIO

У файл `platformio.ini` додав декодер Backtrace:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200

monitor_filters =
  esp32_exception_decoder
  time
```

`esp32_exception_decoder` автоматично бере адреси з Backtrace та порівнює їх із файлом прошивки `.elf`.

## Результат декодування

```text
#0  0x4008344d in panic_abort
#1  0x400880e1 in esp_system_abort
#2  0x4008cf1d in abort
#3  0x400d1444 in loop() at src/main.cpp:22
#4  0x400d3165 in loopTask(void*)
```

## Знайдена помилка

| Що потрібно знайти | Результат                           |
| ------------------ | ----------------------------------- |
| Файл               | `src/main.cpp`                      |
| Номер рядка        | `22`                                |
| Функція            | `loop()`                            |
| Причина crash      | У `loop()` було викликано `abort()` |

## Як читати результат

```text
loop() at src/main.cpp:22
```

означає:

- програма впала під час виконання функції `loop()`;
- проблемний код знаходиться у файлі `src/main.cpp`;
- конкретне місце — рядок `22`.

Шлях до падіння:

```text
loop() → abort() → esp_system_abort() → panic_abort()
```

## Висновок

Backtrace спочатку містив лише адреси пам’яті. Після декодування через `esp32_exception_decoder` стало зрозуміло, що crash був викликаний у функції `loop()` у файлі `src/main.cpp` на рядку `22`.

PS. достаньо _rebuild_ щоб зміни у _platformio.ini_ спрацювали
