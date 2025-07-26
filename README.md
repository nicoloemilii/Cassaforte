# 🔐 Cassaforte elettronica con Arduino

Questo progetto mostra il funzionamento di una **cassaforte elettronica** realizzata con Arduino. È stato sviluppato in ambito scolastico e utilizza componenti elettronici di base per simulare l'apertura con password.

## ⚙️ Funzionamento

La cassaforte funziona tramite:
- Inserimento di un codice PIN tramite tastierino 4x4
- Verifica del codice: se corretto, apertura tramite servo
- Se errato, viene registrato un tentativo fallito
- Dopo 5 tentativi sbagliati, scatta un allarme (LED rosso lampeggiante)

## 🧩 Componenti utilizzati

- Arduino UNO
- Tastiera 4x4
- Servo motore SG90
- LED rosso e verde
- Buzzer piezoelettrico
- Display LCD (opzionale)
- Resistenze

## 💾 Codice

Lo sketch Arduino (`cassaforte.ino`) include:
- Lettura input da tastiera
- Verifica della password
- Comando del servo per apertura/chiusura
- Gestione allarme con LED e buzzer

## 🛠️ Prototipazione

Il progetto è stato realizzato su breadboard con collegamenti volanti, e testato interamente tramite l’IDE Arduino.

## 👨‍💻 Autore

Nicolò Emilii – Progetto scolastico realizzato nel 5º anno.

---

🔗 **Nota**: Questo progetto è stato creato per scopi didattici. Non è destinato a un utilizzo in contesti reali di sicurezza.
