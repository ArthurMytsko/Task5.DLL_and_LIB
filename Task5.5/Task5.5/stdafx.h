// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h>

#define DllImport   __declspec( dllimport )

typedef void __declspec( dllimport ) Function(void);



// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
