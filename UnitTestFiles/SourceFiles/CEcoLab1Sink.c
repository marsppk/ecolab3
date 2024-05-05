/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"
#include <Windows.h>

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_QueryInterface(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoLab1Events ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_AddRef(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_Release(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1Sink((IEcoLab1Events*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

void SetDefault(HANDLE* handle) {
	SetConsoleTextAttribute(*handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void SetWhite(HANDLE* handle) {
	SetConsoleTextAttribute(*handle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
}

void SetGreen(HANDLE* handle) {
	SetConsoleTextAttribute(*handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
}

void SetBlue(HANDLE* handle) {
	SetConsoleTextAttribute(*handle, BACKGROUND_INTENSITY | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void SetRed(HANDLE* handle) {
	SetConsoleTextAttribute(*handle, BACKGROUND_INTENSITY | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

/*
 *
 * <сводка>
 *   Функция OnMyCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_BeginSort(/* in */ struct IEcoLab1Events* me, /* in */ const void* data, size_t size) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
	size_t i;
    int32_t* result = (int32_t*) data;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (me == 0 ) {
        return -1;
    }
	printf("Input array: ");
	SetWhite(&handle);
    for (i = 0; i < size; ++i) {
        printf("%2d ", *(result + i));
    }
	SetDefault(&handle);
    printf("\n");
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_IterCreateBuffSort(/* in */ struct IEcoLab1Events* me, /* in */ const void* buff, size_t buff_size, size_t buff_ind,
	const void* data, size_t data_size, size_t data_ind) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
	size_t i;
    int32_t* result_buff = (int32_t*) buff;
	int32_t* result_data = (int32_t*) data;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (me == 0 ) {
        return -1;
    }
	printf("\rCreating of counting buffer\n");
	SetWhite(&handle);
	for (i = 0; i < data_size; ++i) {
		if (i == data_ind) {
			SetRed(&handle);
			printf("%2d", *(result_data + i));
			printf(" ");
			SetWhite(&handle);
			continue;
		}
        printf("%2d ", *(result_data + i));
    }
	SetDefault(&handle);
	printf("\n\n");
	SetWhite(&handle);
    for (i = 0; i < buff_size; ++i) {
		if (i == buff_ind) {
			SetGreen(&handle);
			printf("%2d", *(result_buff + i));
			printf(" ");
			SetWhite(&handle);
			continue;
		}
        printf("%2d ", *(result_buff + i));
    }
	SetDefault(&handle);
    printf("\n");
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_IterWriteResSort(/* in */ struct IEcoLab1Events* me, /* in */ const void* buff, size_t buff_size, size_t buff_ind,
	const void* data, size_t data_size, size_t data_ind) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
	size_t i;
    int32_t* result_buff = (int32_t*) buff;
	int32_t* result_data = (int32_t*) data;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (me == 0 ) {
        return -1;
    }
	printf("\rRewriting result from buffer into input array\n");
	SetWhite(&handle);
	for (i = 0; i < buff_size; ++i) {
		if (i == buff_ind) {
			SetRed(&handle);
			printf("%2d", *(result_buff + i));
			printf(" ");
			SetWhite(&handle);
			continue;
		}
        printf("%2d ", *(result_buff + i));
    }
	SetDefault(&handle);
	printf("\n\n");
	SetWhite(&handle);
    for (i = 0; i < data_size; ++i) {
		if (i == data_ind) {
			SetGreen(&handle);
			printf("%2d", *(result_data + i));
			printf(" ");
			SetWhite(&handle);
			continue;
		}
        printf("%2d ", *(result_data + i));
    }
	SetDefault(&handle);
    printf("\n");
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_FinishSort(/* in */ struct IEcoLab1Events* me, /* in */ const void* data, size_t size) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
	size_t i;
    int32_t* result = (int32_t*) data;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (me == 0 ) {
        return -1;
    }
	printf("Result: ");
	SetGreen(&handle);
    for (i = 0; i < size; ++i) {
        printf("%2d ", *(result + i));
    }
	SetDefault(&handle);
    printf("\n");
    return 0;
}


/*
 *
 * <сводка>
 *   Функция Advise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_Advise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);

    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*)me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_Unadvise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint * pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie) {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);
        if (result == 0) {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0) {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

/* Create Virtual Table IEcoLab1VTblEvents */
IEcoLab1VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents = {
    CEcoLab1Sink_QueryInterface,
    CEcoLab1Sink_AddRef,
    CEcoLab1Sink_Release,
    CEcoLab1Sink_BeginSort,
	CEcoLab1Sink_IterCreateBuffSort,
	CEcoLab1Sink_IterWriteResSort,
	CEcoLab1Sink_FinishSort
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1Events** ppIEcoLab1Events) {
    int16_t result = -1;
    CEcoLab1Sink* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab1Events == 0 || pIMem == 0 ) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1Sink*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab1Events = &g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents;

    *ppIEcoLab1Events = (IEcoLab1Events*)pCMe;

    return 0;
};

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1Sink(IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
