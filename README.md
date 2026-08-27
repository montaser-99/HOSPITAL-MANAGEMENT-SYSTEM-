# 🏥 Hospital Management System

A **Hospital Management System (HMS)** developed in **C++** using **Object-Oriented Programming (OOP)** and **STL data structures**.

The system simulates core hospital operations such as patient registration, admission and discharge, doctor appointments, emergency management, medical tests, prescriptions, billing, room management, searching, and hospital statistics.

---

## 📌 Project Overview

The Hospital Management System is designed to demonstrate how **OOP concepts and STL data structures** can be used to model real-world hospital workflows.

The system consists of four main classes:

* `Patient`
* `Doctor`
* `EmergencyCase`
* `Hospital`

The `Hospital` class acts as the central controller that manages patients, doctors, appointments, emergencies, rooms, billing, and reporting.

---

## 🚀 Features

### 👤 Patient Management

* Register new patients
* Automatically generate unique patient IDs
* Store patient name, age, and contact information
* Admit patients
* Discharge patients
* Track admission status
* Search patients by name
* Display patient information
* Display all registered patients

### 👨‍⚕️ Doctor Management

* Register doctors
* Automatically generate unique doctor IDs
* Assign doctors to medical departments
* Display doctor information
* Display all doctors

### 📅 Appointment Management

* Book appointments
* FIFO appointment scheduling
* Doctor can see the next waiting patient
* Cancel a specific appointment
* Display doctor appointment queues

### 🚑 Emergency Management

Two different emergency systems are implemented:

#### Standard Emergency Queue

Uses `queue<int>` with **FIFO** behavior.

#### Priority Emergency Queue

Uses `priority_queue<EmergencyCase>` to handle emergencies according to severity.

Severity levels:

```text
1 → Lowest
2
3
4
5 → Highest
```

Higher severity cases are handled first.

### 🧪 Medical Tests

* Request diagnostic tests
* Store pending tests using a FIFO queue
* Perform the first requested test
* Display pending tests
* Automatically add test charges to the patient's bill

Each performed test costs:

```text
$300
```

### 💊 Prescriptions

* Add medicines to a patient's prescriptions
* Display prescribed medicines
* Maintain prescription history
* Automatically add medicine charges

Each prescription costs:

```text
$100
```

### 💰 Billing System

The system automatically calculates patient bills.

#### Room Charges

| Room Type    | Charge |
| ------------ | -----: |
| General Ward |   $500 |
| ICU          | $3,000 |
| Private Room | $1,500 |
| Semi-Private | $1,000 |

#### Other Charges

| Service      | Charge |
| ------------ | -----: |
| Medical Test |   $300 |
| Prescription |   $100 |

Manual bill adjustments are also supported through:

```cpp
addBill(double amount)
```

### 🏨 Room Management

The hospital contains four room categories:

* General Ward — 20 rooms
* ICU — 5 rooms
* Private Rooms — 10 rooms
* Semi-Private Rooms — 10 rooms

The system checks room availability before admitting a patient.

> **Note:** In the current implementation, room counters are checked but are not decremented after admission.

### 📋 Medical History

Patient medical history is implemented using:

```cpp
stack<string>
```

This provides **LIFO (Last In, First Out)** behavior, so the most recent medical event is displayed first.

Medical history includes:

* Patient admission
* Patient discharge
* Test requests
* Performed tests
* Prescriptions

---

## 🧠 Data Structures Used

This project demonstrates several important C++ STL data structures.

| Data Structure   | Usage                | Behavior               |
| ---------------- | -------------------- | ---------------------- |
| `vector`         | Patients & Doctors   | Dynamic collection     |
| `stack`          | Medical History      | LIFO                   |
| `queue`          | Tests & Appointments | FIFO                   |
| `queue`          | Standard Emergencies | FIFO                   |
| `priority_queue` | Priority Emergencies | Highest priority first |

---

## 🏗️ Project Architecture

```text
Hospital Management System
│
├── Patient
│   ├── Personal Information
│   ├── Medical History
│   ├── Test Queue
│   ├── Prescriptions
│   ├── Admission
│   └── Billing
│
├── Doctor
│   ├── Personal Information
│   ├── Department
│   └── Appointment Queue
│
├── EmergencyCase
│   ├── Patient ID
│   └── Severity
│
└── Hospital
    ├── Patients
    ├── Doctors
    ├── Emergency Queue
    ├── Priority Emergency Queue
    ├── Room Management
    └── Hospital Statistics
```

---

## 🧩 OOP Concepts Applied

The project applies several Object-Oriented Programming concepts:

### Encapsulation

Class data members are declared as `private` and accessed through public methods.

### Abstraction

Complex hospital operations are encapsulated inside classes such as `Patient`, `Doctor`, and `Hospital`.

### Composition

The `Hospital` class manages collections of `Patient`, `Doctor`, and `EmergencyCase` objects.

### Constructors

Constructors are used to initialize objects with their required information.

### Operator Overloading

`EmergencyCase` overloads `operator<` to allow `priority_queue` to prioritize emergencies based on severity.

---

## 🔄 Example Workflow

A typical patient workflow is:

```text
Register Patient
       ↓
   Admit Patient
       ↓
Book Doctor Appointment
       ↓
Request Medical Test
       ↓
Perform Medical Test
       ↓
Prescribe Medicine
       ↓
Generate Patient Bill
       ↓
Discharge Patient
```

---

## 🧪 Test Cases

The project includes a comprehensive test harness covering:

* Patient registration
* Doctor registration
* Patient admission
* Duplicate admission
* Appointment booking
* Invalid doctor ID
* Invalid patient ID
* Standard emergency handling
* Priority emergency handling
* Patient information
* Doctor information
* Patient search
* Medical tests
* Prescriptions
* Billing
* Appointment cancellation
* Room status
* Displaying all patients
* Displaying all doctors
* Patient discharge
* Hospital statistics
* Empty hospital edge cases

---

## 💻 Technologies

* **C++**
* **Object-Oriented Programming**
* **STL**
* `vector`
* `stack`
* `queue`
* `priority_queue`

---

## ▶️ How to Run

### Using Visual Studio

1. Clone or download the repository.
2. Open the project in **Visual Studio**.
3. Open the C++ source file.
4. Build the project.
5. Run the application.

### Using g++

The project can also be compiled using C++17:

```bash
g++ -std=c++17 main.cpp -o hospital
```

Then run:

```bash
./hospital
```

---

## 📊 Example Output

```text
Appointment booked for patient 1 with doctor 1
Appointment booked for patient 2 with doctor 1
Appointment booked for patient 3 with doctor 2

Handled emergency for patient: 3
Handled emergency for patient: 1

Emergency added with severity 2
Emergency added with severity 5
Emergency added with severity 3
Emergency added with severity 4

Handling patient 2 with severity 5
Handling patient 1 with severity 4
Handling patient 3 with severity 3
Handling patient 1 with severity 2
```

---

## 📈 Hospital Statistics

The system provides:

* Total number of patients
* Total number of doctors
* Number of admitted patients
* Waiting standard emergencies
* Waiting priority emergencies
* Total generated bills

Example:

```text
========== HOSPITAL STATISTICS ==========
Total Patients: 3
Total Doctors: 3
Admitted Patients: 1
Waiting Emergencies: 0
Priority Emergencies: 0
Total Generated Bills: $5000
=========================================
```

---

## 📁 Project Structure

```text
HOSPITAL-MANAGEMENT-SYSTEM-
│
├── main.cpp
├── README.md
└── ...
```

---

## 🎯 Project Goals

The main goals of this project are to:

* Apply C++ OOP principles to a real-world problem.
* Practice STL data structures.
* Understand FIFO and LIFO workflows.
* Implement priority-based processing.
* Practice class design and encapsulation.
* Build a complete console-based management system.
* Handle invalid inputs and edge cases.

---

## 🔮 Future Improvements

Possible future enhancements include:

* Persistent database storage
* Graphical User Interface (GUI)
* Login and authentication system
* Role-based access control
* More advanced billing and insurance support
* Real room occupancy tracking
* Patient deletion and update operations
* Doctor availability schedules
* Appointment dates and times
* File-based data persistence
* Database integration

---

## 👨‍💻 Author

**Mahmoud Montaser**

C++ | OOP | Backend Development | Software Engineering

---

## 📄 License

This project is developed for **educational and software engineering purposes**.
