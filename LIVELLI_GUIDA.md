# 📖 Documentazione Sistemi Livelli - GraviCLI

## 🎮 Come Funziona il Gioco

**GraviCLI** è un puzzle-game CLI basato su:
- **Gravità orientabile**: Il giocatore deve cambiare direzione gravitazionale per raggiungere l'obiettivo
- **Percorso testuale**: Il giocatore scrive lettere che traccia il suo cammino sulla mappa
- **Meccanica di collisione**: Ostacoli fissi, rimovibili e zone libere

## 🗺️ Sistema di Mappe

### Formato File
Le mappe sono file `.txt` nella cartella `livelli/`. Il sistema di caricamento:
- Legge il file riga per riga
- Determina automaticamente le dimensioni (MAX_Y e MAX_X)
- Gestisce il BOM UTF-8
- Normalizza le righe (rimuove `\r` su Windows)

### Caratteri Disponibili

| Carattere | Tipo | Descrizione |
|-----------|------|-------------|
| `#` | SFONDO | Muro/collisione permanente (non rimovibile) |
| ` ` (spazio) | LIBERO | Zona libera dove muoversi |
| `.` | LIBERO | Proiettile/pick-up (raccoglibile senza collisione) |
| Qualsiasi lettera | COLLISIONE | Ostacolo rimovibile (si rimuove con backspace) |

### Codici di Colore
Nel codice vengono assegnati colori automaticamente:
- `#` → Grigio chiaro (sfondo)
- Lettere → Bianco
- Proiettili `.` → Bianco

## 🎯 Meccaniche di Gioco

### Input del Giocatore
```
Tasti direzionali (↑↓←→): Cambiano la gravità
Lettere normali:           Avanzano nella direzione della gravità
BACKSPACE:                 Rimuove l'ultimo movimento
Comando SKIP:              Salta uno step (se disponibile)
SPARO:                     Dispara proiettili per distruggere ostacoli
D:                         Debug (mostra la griglia)
ESC:                       Esce dal gioco
```

### Gravità
Quattro direzioni possibili:
- **SU** (`^`): Muoversi verso l'alto
- **GIÙ** (`v`): Muoversi verso il basso
- **SINISTRA** (`<`): Muoversi a sinistra
- **DESTRA** (`>`): Muoversi a destra

### Proiettili e Ostacoli
- Ogni `.` raccolto aggiunge 1 proiettile all'inventario
- I proiettili distruggono gli ostacoli (caratteri non-# non-spazio)
- Usare il comando SPARO per sparare nella direzione della gravità attuale

## 📝 Creare un Nuovo Livello

### Template Base
```
##########################################################
#                                                        #
#  inizio                                    fine       #
#                                                        #
##########################################################
```

### Linee Guida di Design

1. **Confini**: Circonda il livello con `#` su tutti i lati
2. **Spazi liberi**: Usa ` ` per le aree dove il giocatore può muoversi
3. **Ostacoli**: Usa lettere (a-z, A-Z) per ostacoli rimovibili
4. **Bonus**: Usa `.` per proiettili collezionabili
5. **Difficoltà**: Aumenta la complessità del percorso

### Esempi di Pattern

#### Corridoio Semplice
```
####################################
# inizio                    fine   #
####################################
```

#### Salti tra Piattaforme
```
####################################
# inizio                           #
#   xxx          yyy        zzz    #
#                                  #
#                                  #
#   aaa          bbb        fine   #
####################################
```

#### Ostacoli da Distruggere
```
####################################
#  start           .   .           #
#  oooo           oooo            #
#  oooo           oooo            #
#  oooo           oooo    end     #
####################################
```

#### Labirinto
```
####################################
#  in  # xxx #      # yyy #        #
#     #     #      #     # out    #
##########  ########  ##########  #
####################################
```

## 🔧 Caricamento Livelli

Nel file `main.cpp`, per caricare un livello:
```cpp
campo.carica_campo("livello1_corridoio.txt");  // Carica dal folder livelli/
campo.inizializza();  // Inizializza i tipi di casella
```

## 📊 Statistiche Consigliate

| Aspetto | Valore Consigliato |
|---------|------------------|
| Larghezza | 50-100 caratteri |
| Altezza | 15-40 righe |
| Ostacoli | 10-30% della mappa |
| Proiettili | 2-5 per livello |
| Complessità | Aumentare gradualmente |

## 🎨 Colori

Il gioco supporta 16 colori ANSI per il testo e sfondo:
- Primari: Nero, Rosso, Verde, Giallo, Blu, Magenta, Ciano, Bianco
- Varianti: chiaro, scuro, etc.

I colori sono assegnati automaticamente:
- Sfondo `#` usa `Colore::grigio_chiaro`
- Ostacoli e proiettili usano `Colore::bianco`

## 💡 Tips di Design

1. **Progressione**: Inizia semplice e aumenta la difficoltà
2. **Chiarezza**: Usa spazi per separare le sezioni
3. **Feedback**: La freccia grafica mostra la prossima posizione
4. **Prova visivamente**: Usa il comando DEBUG (D) per visualizzare la mappa

## 🚀 Livelli Creati

1. **livello1_corridoio.txt** - Corridoio semplice (Principiante)
2. **livello2_labirinto.txt** - Navigazione complessa (Intermedio)
3. **livello3_salti_gravita.txt** - Cambio di gravità frequente (Intermedio)
4. **livello4_puzzle.txt** - Raccolta proiettili (Avanzato)
5. **livello5_spirale.txt** - Percorso a spirale (Avanzato)

---
**Data creazione**: 2026-04-14
**Versione**: 1.0

