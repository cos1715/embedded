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
20:16:25.128 > Backtrace: 0x4008344d:0x3ffb2190 0x400880e1:0x3ffb21b0 0x4008cf1d:0x3ffb21d0 0x400d1422:0x3ffb2250 0x400d13fb:0x3ffb2270 0x400d30a5:0x3ffb2290
20:16:25.229 >   #0  0x4008344d in panic_abort at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/esp_system/panic.c:408
20:16:25.229 >   #1  0x400880e1 in esp_system_abort at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/esp_system/esp_system.c:137
20:16:25.229 >   #2  0x4008cf1d in abort at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/newlib/abort.c:46
20:16:25.229 >   #3  0x400d1422 in task1Loop() at src/tasks/task1_crash.cpp:12
20:16:25.229 >   #4  0x400d13fb in loop() at src/main.cpp:12
20:16:25.229 >   #5  0x400d30a5 in loopTask(void*) at /Users/tarassamoilenko/.platformio/packages/framework-arduinoespressif32/cores/esp32/main.cpp:50
```

## Знайдена помилка

| Що потрібно знайти | Результат                           |
| ------------------ | ----------------------------------- |
| Файл               | `src/main.cpp`                      |
| Номер рядка        | `12`                                |
| Функція            | `loop()`                            |
| Причина crash      | У `loop()` було викликано `abort()` |

## Як читати результат

```text
loop() at src/main.cpp:12
```

означає:

- програма впала під час виконання функції `loop()`;
- проблемний код знаходиться у файлі `src/main.cpp`;
- конкретне місце — рядок `12`.

Шлях до падіння:

```text
loop() → abort() → esp_system_abort() → panic_abort()
```

## Висновок

Backtrace спочатку містив лише адреси пам’яті. Після декодування через `esp32_exception_decoder` стало зрозуміло, що crash був викликаний у функції `loop()` у файлі `src/main.cpp` на рядку `12`.

PS. достаньо _rebuild_ щоб зміни у _platformio.ini_ спрацювали
