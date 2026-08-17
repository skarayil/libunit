# 🧪 libunit - C Unit Test Framework

<div align="center">

![42 School](https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Library](https://img.shields.io/badge/Project-libunit-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)

**C projeleri için process-izolasyonlu, sinyal-farkında bir unit test framework'ü**

*libunit, her test case'ini ayrı bir process'te (fork) çalıştırarak segfault, bus error, abort gibi çökmeleri tek bir testin sınırında tutar; bu sayede tek bir hatalı test, test suite'inin tamamını düşürmez.*

[Kurulum](#-kurulum) • [Kullanım](#-kullanım) • [Nasıl Çalışır](#-nasıl-çalışır) • [Test Senaryoları](#-test-senaryoları)

</div>

---

## 🎯 Projenin Amacı

<img align="right" alt="Library Animation" width="300" src="https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExZnBreWp5N2NleG90dTN3Z3JrcHNvMnE3dmUyZTgybXd6aTUwcGx2ayZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/11ZSwQNWba4YF2/giphy.gif">

Bu proje, C'de yazılmış fonksiyonları/kütüphaneleri test etmek için **kendi unit test framework'ümü** oluşturmayı amaçlamaktadır. Klasik `assert()` tabanlı test yaklaşımlarının en büyük sorunu, bir testin segfault vermesi durumunda tüm test binary'sinin çökmesidir. libunit bu sorunu **her testi `fork()` ile ayrı bir child process'te çalıştırarak** çözer.

### 🎓 **Öğrenme Hedefleri:**

#### 🧠 **Process Yönetimi**
- `fork()` / `waitpid()` ile process izolasyonu
- Parent-child process iletişimi ve exit status analizi
- Child process'te çöken testlerin parent'ı etkilememesi

#### 🚦 **Sinyal Analizi**
- `WIFEXITED` / `WIFSIGNALED` / `WEXITSTATUS` / `WTERMSIG` makrolarının kullanımı
- SIGSEGV, SIGBUS, SIGABRT, SIGFPE, SIGPIPE, SIGILL, SIGALRM sinyallerinin ayırt edilmesi
- Çökme nedenine göre anlamlı hata sınıflandırması

#### 🏗️ **Veri Yapıları ve Modüler Tasarım**
- Bağlı liste (`t_unit_test`) ile dinamik test kaydı
- Dinamik büyüyen sonuç buffer'ı (`t_result_buf`)
- Renkli, okunabilir terminal çıktısı

---

## 📁 Proje Yapısı

```
libunit/
│
├── 📋 libunit.a                     # Derlenmiş statik kütüphane (make sonrası)
│
└── 📂 framework/
    ├── 🔨 Makefile                  # Build automation - derleme kuralları
    │
    ├── 📂 include/
    │   ├── libunit.h                # Struct/enum tanımları ve fonksiyon prototipleri
    │   └── colors.h                 # ANSI renk kodları
    │
    ├── 📂 sources/
    │   ├── load_test.c              # Test kaydı (bağlı liste)
    │   ├── launch_tests.c           # Ana orkestrasyon (çalıştır + yazdır + temizle)
    │   ├── signal_analyzer.c        # fork + waitpid + exit/sinyal analizi
    │   └── print_utils.c            # Renkli sonuç raporlama
    │
    └── 📂 objects/                  # Object dosyaları (make sonrası oluşur)
```

---

## ⚙️ Nasıl Çalışır

libunit, bir test suite'ini şu akışla işler:

1. **Kayıt** — `ft_load_test` ile her test, `func` (test edilen fonksiyon adı) ve `name` (test adı) etiketleriyle birlikte bir bağlı listeye eklenir.
2. **Çalıştırma** — `ft_launch_tests`, listedeki test sayısı kadar yer ayırıp her testi sırayla `ft_run_one` ile çalıştırır. Her test, `fork()` ile oluşturulan ayrı bir child process içinde çalışır; test fonksiyonunun dönüş değeri child'ın exit code'u olur.
3. **Analiz** — Parent process, `waitpid` ile child'ı bekler ve `ft_analyze` fonksiyonuyla exit status'ü inceler:
   - Normal çıkış + exit code `0` → `STATUS_OK`
   - Normal çıkış + exit code `≠0` → `STATUS_KO`
   - Sinyalle sonlanma → sinyale göre `STATUS_SEGV` / `STATUS_BUS` / `STATUS_ABRT` / `STATUS_FPE` / `STATUS_PIPE` / `STATUS_ILL` / `STATUS_TIMEOUT`
4. **Raporlama** — `ft_print_all`, her test sonucunu `fonksiyon: test_adı : [DURUM]` biçiminde, duruma özel renkte ekrana yazar ve sonunda `geçen/toplam` özetini verir.
5. **Temizlik** — `ft_launch_tests`, sonuç buffer'ını ve test listesini serbest bırakır, tüm testler geçtiyse `0`, aksi halde `-1` döner.

> ⏱️ **Not:** `STATUS_TIMEOUT`, `SIGALRM` sinyaline karşılık gelir. Bir testi zaman aşımına karşı korumak isterseniz, test fonksiyonunuzun içinde `alarm(n)` çağırmanız gerekir; libunit bu sinyali yakalayıp uygun şekilde raporlar.

---

## 🚦 Sinyal Kontrolleri (Detaylı)

libunit'in kalbi, her testin child process'ten dönen **exit status'ünü** yorumlayan `ft_analyze` fonksiyonudur (`signal_analyzer.c`). Bu bölüm, o analizin adım adım nasıl işlediğini açıklar.

### 1️⃣ İki Aşamalı Kontrol: `WIFEXITED` vs `WIFSIGNALED`

`waitpid(pid, &wstatus, 0)` çağrısından dönen `wstatus`, ham bir bitmask'tir; doğrudan okunamaz. `ft_analyze` önce çocuğun **nasıl** sonlandığını sorar:

```c
t_status ft_analyze(int status)
{
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 0)
            return (STATUS_OK);
        return (STATUS_KO);
    }
    if (WIFSIGNALED(status))
        return (ft_get_signal(WTERMSIG(status)));
    return (STATUS_UNKNOWN);
}
```

| Makro | Ne zaman `true` döner? | libunit'te kullanımı |
|---|---|---|
| `WIFEXITED(status)` | Process `return`/`exit()` ile **normal** şekilde sonlandıysa | `true` ise `WEXITSTATUS` ile gerçek dönüş kodu okunur → `0` ise `STATUS_OK`, değilse `STATUS_KO` |
| `WEXITSTATUS(status)` | (yalnızca `WIFEXITED` true iken anlamlı) | Test fonksiyonunun `return` ettiği değeri (0-255 arası) verir |
| `WIFSIGNALED(status)` | Process bir **sinyal yüzünden** sonlandıysa (crash, kill, timeout vb.) | `true` ise `WTERMSIG` ile hangi sinyalin geldiği okunur ve `ft_get_signal`'a devredilir |
| `WTERMSIG(status)` | (yalnızca `WIFSIGNALED` true iken anlamlı) | Process'i sonlandıran sinyal numarasını verir (`SIGSEGV`, `SIGABRT`, ...) |

Her iki koşul de `false` ise (ör. process durdurulmuş/stop edilmişse), `ft_analyze` güvenli tarafta kalarak `STATUS_UNKNOWN` döner.

### 2️⃣ Sinyal Numarasından Anlamlı Statüye: `ft_get_signal`

`WTERMSIG` ham bir sinyal numarası (`int`) döndürdüğü için, bu numara `ft_get_signal` ile framework'ün kendi `t_status` enum değerine eşlenir:

```c
static t_status ft_get_signal(int sig)
{
    if (sig == SIGSEGV) return (STATUS_SEGV);
    if (sig == SIGBUS)  return (STATUS_BUS);
    if (sig == SIGABRT) return (STATUS_ABRT);
    if (sig == SIGFPE)  return (STATUS_FPE);
    if (sig == SIGPIPE) return (STATUS_PIPE);
    if (sig == SIGILL)  return (STATUS_ILL);
    if (sig == SIGALRM) return (STATUS_TIMEOUT);
    return (STATUS_UNKNOWN);
}
```

Bu eşleme sayesinde raporlama katmanı (`print_utils.c`), ham bir sinyal numarasıyla değil, anlamlı bir `t_status` değeriyle çalışır.

### 3️⃣ Sinyal Sinyal: Hangi Durumda Hangisi Tetiklenir?

| Sinyal | `t_status` | Tipik Tetikleyici | Örnek Test Hatası |
|---|---|---|---|
| `SIGSEGV` | `STATUS_SEGV` | Geçersiz bellek erişimi | `NULL` pointer dereference, dizi sınırı dışına yazma, `free` edilmiş belleğe erişim |
| `SIGBUS` | `STATUS_BUS` | Hizalanmamış (misaligned) bellek erişimi ya da geçersiz bellek eşlemesi | Yanlış tipte pointer cast'lenip dereference edilmesi, mmap sınırları dışı erişim |
| `SIGABRT` | `STATUS_ABRT` | Programın kendi kendini sonlandırması | `abort()` çağrısı, başarısız bir `assert()`, glibc'nin heap bozulması (`double free`, `free()` sonrası use) tespiti |
| `SIGFPE` | `STATUS_FPE` | Aritmetik hata | Sıfıra bölme (`x / 0`), `INT_MIN / -1` gibi taşan tam sayı bölmesi |
| `SIGPIPE` | `STATUS_PIPE` | Kapalı bir pipe/socket'e yazma | Karşı taraf kapanmış bir `write()` çağrısı |
| `SIGILL` | `STATUS_ILL` | Geçersiz/bozuk makine komutu çalıştırma | Bozulmuş function pointer'a atlama, corrupt edilmiş kod belleği |
| `SIGALRM` | `STATUS_TIMEOUT` | Zamanlayıcı süresi doldu | Testin içinde `alarm(n)` çağrılmış ve `n` saniye içinde test bitmemiş (ör. sonsuz döngü, deadlock) |
| *(diğer tüm sinyaller)* | `STATUS_UNKNOWN` | `ft_get_signal`'ın tanımadığı herhangi bir sinyal | ör. `SIGTERM`, `SIGKILL` gibi framework'ün özel olarak ele almadığı sinyaller |

### 4️⃣ Neden `fork()` Olmadan Bu Kontroller İşe Yaramaz?

Bu sinyal analizinin tamamı, `ft_run_one` içinde her testin **ayrı bir child process**'te (`fork()`) çalıştırılmasına dayanır:

```c
pid = fork();
if (pid == 0)
{
    result = lst->test();
    exit(result);          // normal dönüş -> WIFEXITED yolunu tetikler
}
```

Test fonksiyonu bir sinyal yüzünden çökerse (`SIGSEGV` vb.), işletim sistemi **çekirdek seviyesinde** child process'i sonlandırır; parent bunu asla göremez, sadece `waitpid` ile "bu process bir sinyalle öldü" bilgisini alır. Eğer testler fork edilmeden tek process içinde çalıştırılsaydı, aynı sinyal doğrudan test framework'ünün kendisini (ve dolayısıyla kalan tüm testleri) öldürürdü. `fork()` + `waitpid()` + `WIFSIGNALED`/`WTERMSIG` üçlüsü, bu izolasyonu ve sinyalin doğru şekilde raporlanmasını mümkün kılan temel mekanizmadır.

### 5️⃣ Sinyal Analizi Akış Şeması

```
        fork()
          │
   ┌──────┴──────┐
   │             │
 child          parent
   │             │
lst->test()   waitpid(pid, &wstatus, 0)
   │             │
exit(result)   ft_analyze(wstatus)
                  │
        ┌─────────┴─────────┐
        │                   │
   WIFEXITED?           WIFSIGNALED?
        │                   │
  WEXITSTATUS == 0?    ft_get_signal(WTERMSIG)
   │         │               │
 OK         KO      SEGV/BUS/ABRT/FPE/PIPE/ILL/TIMEOUT
```

---

```c
int my_test(void);   // 0 dönerse PASS, 0 dışı bir değer dönerse FAIL
```

---

## 🚀 Kurulum

### 📋 **Ön Gereksinimler**

![GCC](https://img.shields.io/badge/GCC-Required-red?style=flat-square&logo=gnu&logoColor=white)
![Make](https://img.shields.io/badge/Make-Required-blue?style=flat-square&logo=gnu&logoColor=white)
![Unix](https://img.shields.io/badge/Unix-Compatible-green?style=flat-square&logo=linux&logoColor=white)

- **C Compiler**: `gcc` veya `clang`
- **Make**: Build automation tool
- **Unix-like System**: Linux, macOS, WSL (fork/waitpid gerektirir)

### 🔨 **Derleme**

```bash
cd framework
make            # framework/../libunit.a dosyasını üretir (yani proje kökünde libunit.a)

make clean      # objects/ altındaki .o dosyalarını siler
make fclean     # .o dosyalarını ve libunit.a'yı siler, objects/ dizinini kaldırır
make re         # fclean + all
```

---

## 💻 Kullanım

### 🔗 **Projenize Entegrasyon**

```bash
# 1. Kütüphaneyi derleyin
cd framework && make

# 2. Test dosyanızda kullanın
gcc -Wall -Wextra -Werror main_tests.c -Iframework/include -L. -lunit -o run_tests

# 3. Çalıştırın
./run_tests
```

### 📝 **Kod Örneği**

```c
#include "libunit.h"
#include <stdlib.h>

static int test_strlen_empty(void)
{
    return (ft_strlen("") == 0 ? 0 : 1);
}

static int test_strlen_basic(void)
{
    return (ft_strlen("Hello") == 5 ? 0 : 1);
}

static int test_strdup_crashes_on_null(void)
{
    ft_strdup(NULL);   // implementasyon bu durumda segfault veriyorsa
    return (1);         // buraya asla ulaşılmayacak, framework SIGSEGV'i yakalar
}

int main(void)
{
    t_unit_test *lst;
    int          ret;

    lst = NULL;
    ft_load_test(&lst, "ft_strlen", "empty string", test_strlen_empty);
    ft_load_test(&lst, "ft_strlen", "basic string", test_strlen_basic);
    ft_load_test(&lst, "ft_strdup", "null input", test_strdup_crashes_on_null);
    ret = ft_launch_tests(&lst);
    return (ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
```

Örnek çıktı:

```
ft_strlen: empty string : [OK]
ft_strlen: basic string : [OK]
ft_strdup: null input : [SIGSEGV]
2/3 tests checked
```
---

## 🛠️ Teknik Detaylar

### 🔍 Neden fork() tabanlı izolasyon?

Bir test fonksiyonu segfault, bus error ya da abort gibi bir durumla çökerse, bu çökme **sadece o testin child process'ini** sonlandırır. Parent process, `waitpid` ile bu durumu tespit eder ve normal bir test sonucu gibi raporlar; test suite'inin tamamı çalışmaya devam eder. Bu, klasik `assert()`/tek-process yaklaşımlarına göre en büyük avantajdır.

### 🧵 Bellek ve Kaynak Yönetimi

- `ft_load_test`, her test için `malloc` ile bir `t_unit_test` node'u ayırır.
- `ft_launch_tests`, sonuç buffer'ını (`t_result_buf`) test sayısı kadar önceden ayırır, kullanım sonunda serbest bırakır.
- Tüm testler çalıştırıldıktan sonra bağlı liste tamamen `free` edilir (`ft_free_list`).

---

## 📚 Notlar

### ⚠️ **Dikkat Edilmesi Gerekenler**

- Test fonksiyonları `int (*)(void)` imzasına uymalıdır; `0` dönüşü PASS, diğer her değer KO olarak yorumlanır.
- Zaman aşımı koruması otomatik değildir — testin kendisi `alarm()` çağırmalıdır.
- `malloc` başarısız olursa (`ft_buf_init`), `ft_launch_tests` `-1` döner ve hiçbir test çalıştırılmaz.
- Framework, `fork`/`waitpid` kullandığından Unix-benzeri (Linux, macOS) sistemlerde çalışır.

### 💡 **Best Practices**

1. Her test tek bir davranışı doğrulamalıdır (tek sorumluluk prensibi).
2. `func` alanını, test edilen gerçek fonksiyonun adıyla tutarlı tutun — raporda gruplama sağlar.
3. Çökme senaryolarını ayrı test case'leri olarak yazmaktan çekinmeyin; framework bunları güvenle izole eder.
4. `ft_launch_tests`'in dönüş değerini CI/CD pipeline'ınızda exit code olarak kullanın.

---

<div align="center">

**📝 "Libunit lets your test crash — without taking down the rest of the suite."**

---

### 👨‍💻 Created by Sude Naz Karayıldırım

[![42 Profile](https://img.shields.io/badge/42%20Profile-skarayil-black?style=flat-square&logo=42&logoColor=white)](https://profile.intra.42.fr/users/skarayil)
[![GitHub](https://img.shields.io/badge/GitHub-skarayil-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/skarayil)

**⭐ Eğer bu proje işinize yaradıysa, repo'ya star vermeyi unutmayın!**

</div>
