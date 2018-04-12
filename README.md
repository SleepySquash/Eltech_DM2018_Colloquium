# Eltech_DM2018
Discrete Math's project of 7301, 7305 and 7307 collaboration, 2018, LETI, Saint-Petersburg

Данный проект является коллоквиумом по дисциплине "Дискретная математика" университета СПбГЭТУ (ЛЭТИ) 2018 года. Выполнен студентами первого курса групп 7301, 7305, 7307.
Преподаватель: Поздняков Сергей Николаевич.

## Компиляция и использование

Проект выполнен на языке С/С++ в среде Microsoft Visual Studio 2013 студентами групп 7301, 7305 и 7307.
Протестировано на следующих компиляторах: Visual Studio 2013+, GNU 4.7+, clang-700+

_getch() читает вводимый символ с клавиатуры без вывода его на экран консоли.
Коды для _getch():
 72 - стрелка вверх.
 80 - стрелка вниз.
 13 - Enter.
 27 - Esc.
Коды для остальных кнопок можно получить из интернета или простейшим присвоением _getch() переменной типа int, а затем выводом этой самой переменной.
 
Переменные, используемые в меню:
 index - счётчик-номер строки.
 tmp - временная переменная, хранящая в себе введённый символ.
 module - массивы с выводимыми строками (для каждой функции свой массив).
 prevIndex - счётчик-номер, который проверяет изменение индекса.
 
Сдвиг курсора (знака >) во всех функциях производится с помощью одинакового использования _getch() и работы с результатом функции.
Алгоритм сам по себе элементарный: если номер _getch() равен коду кнопки стрелки вверх, то уменьшение индекса, аналогично для стрелки вниз.
Также проводятся проверки, что индексы не выйдут за границы массивов module.

Выполнение программы строится по типу: функция, хранящая в себе функции, каждая из которых в себе хранит функции, которые, в свою очередь, также хранят в себе функции

Каждая новая версия программы несёт в себе малые (и не малые) изменения, которые значительно влияют и улучшают (а также дополняют) саму программу.
То есть каждая новая программа по факту является улучшенной и оптимизированной версией каждой предыдущей. 
Первая цифра версии обозначает количество раз, сколько раз код был написан заново.
Вторая цифра версии обозначает количество раз, когда уже в созданном коде были внесены значительные крупные изменения.
Третья цифра версии обозначает количество раз, когда уже в созданном коде были внесены значительные малые изменения.
Подробнее о каждой версии можно посмотреть в пункте меню I уровня под названием "Помощь".

Список заданий можно увидеть по ссылке - http://pozdnkov.vm2-leti.spb.ru/ucebnye-gruppy-1/plany-lekcij/kollokvium-po-dm/kollokvium-po-dm-2
Список распределений заданий по команде разработки - https://docs.google.com/spreadsheets/d/1X-aLv9Yl9oKm5RbzMNQT9eqwkyXjf6FtmMNYhdbeCRA/edit#gid=0

По поводу уровней меню:
 I уровень - главное меню
 II уровень - модули
 III уровень - функции

# Команда
Архитектор:                         
Дмитрий Кезлинг, 7305               
		                                  
Ответственный по качеству:            
Никита Исаенко,  7305               

Программисты:
Диана Щебет,      7307;
Евгений Сысенко,  7307;
Дмитрий Богряков, 7307
Рустам Аминов,    7307
Анна Волкова,     7307
Владислав Лагерев, 7307
Алина Белоусова,  7307
Алексаднр Трифонов, 7301
Максим Кортель,   7301
Станислав Смирнов,  7301
