// Подключаем необходимые заголовочные файлы
#include <windows.h>   // Основной заголовок Windows API (содержит объявления всех функций WinAPI)
#include "resource.h"  // Заголовочный файл с идентификаторами элементов управления (генерируется автоматически)

// Глобальная переменная для хранения состояния выбранной радио-кнопки
// 1 соответствует IDC_RADIO1, 2 - IDC_RADIO2
int g_nSelectedRadio = 1;

// Основная процедура обработки сообщений диалогового окна
// hwnd - дескриптор окна диалога
// uMsg - код сообщения (например, WM_INITDIALOG, WM_COMMAND и т.д.)
// wParam и lParam - параметры сообщения
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Анализируем тип полученного сообщения
    switch (uMsg) {

        // Сообщение инициализации диалогового окна (при первом показе)
    case WM_INITDIALOG:
        // Устанавливаем первую радио-кнопку как выбранную по умолчанию
        // CheckRadioButton автоматически снимает выбор с других кнопок в группе
        // Параметры:
        // hwnd - дескриптор окна
        // IDC_RADIO1 - ID первой кнопки в группе
        // IDC_RADIO2 - ID последней кнопки в группе
        // IDC_RADIO1 - ID кнопки, которую нужно выбрать
        CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

        // Возвращаем TRUE, чтобы система установила фокус ввода на элемент по умолчанию
        return TRUE;

        // Обработка команд от элементов управления
    case WM_COMMAND:
        // LOWORD(wParam) содержит ID элемента, от которого пришло сообщение
        switch (LOWORD(wParam)) {

            // Обработка нажатия кнопки OK
        case IDOK:
        {
            // Определяем, какая радио-кнопка выбрана
            // IsDlgButtonChecked возвращает BST_CHECKED, если кнопка выбрана
            g_nSelectedRadio = IsDlgButtonChecked(hwnd, IDC_RADIO1) ? 1 : 2;

            // Создаем буфер для сообщения (100 символов Unicode)
            WCHAR szMsg[100];

            // Формируем строку сообщения с номером выбранной кнопки
            // wsprintf - аналог sprintf для широких строк (Unicode)
            wsprintf(szMsg, L"Выбрана радио-кнопка: %d", g_nSelectedRadio);

            // Показываем сообщение с результатом
            MessageBox(hwnd, szMsg, L"Информация", MB_OK);

            // Закрываем диалоговое окно с результатом TRUE
            EndDialog(hwnd, TRUE);

            // Возвращаем TRUE, сообщая, что сообщение обработано
            return TRUE;
        }

        // Обработка кнопки Cancel
        case IDCANCEL:
            // Закрываем диалоговое окно с результатом FALSE
            EndDialog(hwnd, FALSE);
            return TRUE;

            // Обработка выбора первой радио-кнопки
        case IDC_RADIO1:
            // Явно устанавливаем выбор на первую кнопку
            CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

            // Обновляем глобальную переменную
            g_nSelectedRadio = 1;
            return TRUE;

            // Обработка выбора второй радио-кнопки
        case IDC_RADIO2:
            // Явно устанавливаем выбор на вторую кнопку
            CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);

            // Обновляем глобальную переменную
            g_nSelectedRadio = 2;
            return TRUE;

            // Обработка кнопки "Переключить"
        case IDC_BUTTON_TOGGLE:
            // Проверяем, какая кнопка сейчас выбрана
            if (IsDlgButtonChecked(hwnd, IDC_RADIO1)) {
                // Если выбрана первая - переключаем на вторую
                CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
                g_nSelectedRadio = 2;
            }
            else {
                // Иначе переключаем на первую
                CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
                g_nSelectedRadio = 1;
            }
            return TRUE;
        }
        break;  // Выход из switch(wParam)
    }

    // Если сообщение не обработано, возвращаем FALSE
    return FALSE;
}

// Точка входа Windows-приложения
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,      // Дескриптор экземпляра приложения
    _In_opt_ HINSTANCE hPrevInstance, // Всегда NULL (оставлено для совместимости)
    _In_ LPSTR lpCmdLine,          // Аргументы командной строки (ANSI-строка)
    _In_ int nCmdShow)             // Параметры отображения окна
{
    // Создаем и отображаем модальное диалоговое окно:
    DialogBox(
        hInstance,                 // Дескриптор экземпляра приложения
        MAKEINTRESOURCE(IDD_DIALOG1), // Ресурсный ID диалога (преобразуется в строку)
        NULL,                      // Родительское окно (нет)
        DialogProc);               // Функция обработки сообщений

    // Возвращаем 0 - успешное завершение
    return 0;
}

