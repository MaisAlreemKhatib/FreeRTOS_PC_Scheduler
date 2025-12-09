#include "scheduler.h"

// Basit ANSI renk kodlari - GENİŞ PALET (her task farklı renk alır)
static const char *color_table[] = {
    "\x1b[31m", // kırmızı
    "\x1b[32m", // yeşil
    "\x1b[33m", // sarı
    "\x1b[34m", // mavi
    "\x1b[35m", // mor
    "\x1b[36m", // camgöbeği
    "\x1b[91m",
    "\x1b[92m",
    "\x1b[93m",
    "\x1b[94m",
    "\x1b[95m",
    "\x1b[96m",
    "\x1b[90m",
    "\x1b[37m",
    "\x1b[97m"
};



static const char *color_reset = "\x1b[0m";

static const char *get_color(int idx)
{
    int n = sizeof(color_table) / sizeof(color_table[0]);
    if (idx < 0) idx = 0;
    return color_table[idx % n];
}



// ---- Zaman formatı ----
static void print_time_ms(int t)
{
    printf("%d.0000 sn", t);
}

// Görev başlarken
void task_log_start(Task *task, int now)
{
    const char *c = get_color(task->color_index);
    printf("%s", c);
    print_time_ms(now);

    if (task->base_priority == 0) {  
        printf(" task%d basladi (id:%04d, oncelik=0, kalan=%d s)%s\n",
               task->id, task->id, task->remaining_time, color_reset);
    } else {
        printf(" task%d basladi (id:%04d, kullanici oncelik=%d, kuyruk=%d, kalan=%d s)%s\n",
               task->id, task->id, task->base_priority, task->current_queue,
               task->remaining_time, color_reset);
    }
}

// Her saniye çalışırken
void task_log_tick(Task *task, int now)
{
    const char *c = get_color(task->color_index);
    printf("%s", c);
    print_time_ms(now);
    printf(" task%d yurutuluyor (id:%04d, oncelik=%d, kuyruk=%d, kalan=%d s)%s\n",
           task->id, task->id, task->base_priority, task->current_queue,
           task->remaining_time, color_reset);
}

// Askıya alınırken
void task_log_suspend(Task *task, int now, int new_queue_level)
{
    const char *c = get_color(task->color_index);
    printf("%s", c);
    print_time_ms(now);

    if (task->base_priority == 0) {
        printf(" task%d askida/bitti (id:%04d, kalan=%d s)%s\n",
               task->id, task->id, task->remaining_time, color_reset);
    } else {
        printf(" task%d askida (id:%04d, yeni kuyruk=%d, kalan=%d s)%s\n",
               task->id, task->id, new_queue_level, task->remaining_time,
               color_reset);
    }
}

// Devam ederken
void task_log_resume(Task *task, int now)
{
    const char *c = get_color(task->color_index);
    printf("%s", c);
    print_time_ms(now);
    printf(" task%d devam ediyor (id:%04d, oncelik=%d, kuyruk=%d, kalan=%d s)%s\n",
           task->id, task->id, task->base_priority, task->current_queue,
           task->remaining_time, color_reset);
}

// Bitince
void task_log_finish(Task *task, int now)
{
    const char *c = get_color(task->color_index);
    printf("%s", c);
    print_time_ms(now);
    printf(" task%d sonlandi (id:%04d, oncelik=%d, kalan=0 s)%s\n",
           task->id, task->id, task->base_priority, color_reset);
}
