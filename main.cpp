#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


// =====================================================
// ==================== STORY 1 ========================
// =====================================================
// ENUMERATIONS
// EMERGENCY CASE CLASS
// PATIENT CLASS - BASIC FEATURES
// =====================================================


// ========== ENUMERATIONS ========== //

enum Department {
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType {
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};


// ========== EMERGENCY CASE CLASS ========== //
// Advanced Feature: priority_queue

class EmergencyCase {
private:
    int patientId;
    int severity;

public:
    EmergencyCase(int pid, int s);

    int getPatientId() const;
    int getSeverity() const;

    // Higher severity = higher priority
    bool operator<(const EmergencyCase& other) const;
};


// ========== PATIENT CLASS ========== //

class Patient {
private:
    int id;
    string name;
    int age;
    string contact;

    // Data Structures
    stack<string> medicalHistory;
    queue<string> testQueue;
    vector<string> prescriptions;

    bool isAdmitted;
    RoomType roomType;

    // Advanced Feature: Billing
    double bill;

public:

    // Constructor
    Patient(int pid, string n, int a, string c);


    // ========== ORIGINAL FEATURES ========== //

    void admitPatient(RoomType type);

    void dischargePatient();

    void addMedicalRecord(string record);

    void requestTest(string testName);

    string performTest();

    void displayHistory();

    int getId();

    string getName();

    bool getAdmissionStatus();


    // =====================================================
    // ==================== STORY 2 ========================
    // =====================================================
    // PATIENT ADVANCED FEATURES
    // MEDICAL TESTS
    // PRESCRIPTIONS
    // BILLING
    // ADDITIONAL GETTERS
    // =====================================================

    // Medical Tests
    void displayPendingTests();


    // Prescriptions
    void addPrescription(string medicine);

    void displayPrescriptions();


    // Billing
    void addBill(double amount);

    double getBill();

    void displayBill();


    // Additional Getters
    int getAge();

    string getContact();

    RoomType getRoomType();
};


// =====================================================
// ==================== STORY 3 ========================
// =====================================================
// DOCTOR CLASS
// APPOINTMENT MANAGEMENT
// =====================================================

class Doctor {
private:
    int id;
    string name;
    Department department;

    // Queue of patients waiting for doctor
    queue<int> appointmentQueue;

public:
    // Constructor
    Doctor(int did, string n, Department d) {
        id = did;
        name = n;
        department = d;
    }

    static string departmentName(Department d) {
        switch (d) {
            case CARDIOLOGY:  return "Cardiology";
            case NEUROLOGY:   return "Neurology";
            case ORTHOPEDICS: return "Orthopedics";
            case PEDIATRICS:  return "Pediatrics";
            case EMERGENCY:   return "Emergency";
            case GENERAL:     return "General";
        }
        return "Unknown";
    }

    // ========== ORIGINAL FEATURES ========== //

    void addAppointment(int patientId) {
        appointmentQueue.push(patientId);
    }

    int seePatient() {
        if (appointmentQueue.empty()) {
            return -1;
        }

        int result = appointmentQueue.front();
        appointmentQueue.pop();

        return result;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getDepartment() {
        return departmentName(department);
    }


    // ========== NEW FEATURES ========== //

    // Display waiting patients
    void displayAppointments() {
        int n = appointmentQueue.size();
        for (int i = 0; i < n; i++) {
            int currentPatientId = appointmentQueue.front();
            appointmentQueue.pop();

            cout << currentPatientId << " ";

            appointmentQueue.push(currentPatientId);
        }

        cout << endl;
    }


    // Cancel appointment
    void cancelAppointment(int patientId) {
        int n = appointmentQueue.size();
        for (int i = 0; i < n; i++) {
            int currentPatientId = appointmentQueue.front();
            appointmentQueue.pop();

            if (patientId != currentPatientId) {
                appointmentQueue.push(currentPatientId);
            }
        }
    }


    // Number of waiting patients
    int getAppointmentCount() {
        return appointmentQueue.size();
    }
};


// =====================================================
// ==================== STORY 4 ========================
// =====================================================
// HOSPITAL CORE FEATURES
// HOSPITAL CONSTRUCTOR
// PATIENT REGISTRATION
// DOCTOR REGISTRATION
// ADMISSION
// FIND PATIENT
// FIND DOCTOR
// APPOINTMENTS
// NORMAL EMERGENCY
// BASIC INFORMATION DISPLAY
// =====================================================

class Hospital {
private:

    // Main collections
    vector<Patient> patients;

    vector<Doctor> doctors;


    // Original emergency queue
    queue<int> emergencyQueue;


    // Advanced emergency queue
    priority_queue<EmergencyCase> priorityEmergencyQueue;


    // Counters
    int patientCounter;

    int doctorCounter;


    // ========== ROOM MANAGEMENT ========== //

    int generalRooms;

    int icuRooms;

    int privateRooms;

    int semiPrivateRooms;


public:

    // Constructor
    Hospital();


    // =====================================================
    // PATIENT & DOCTOR REGISTRATION
    // =====================================================

    int registerPatient(
        string name,
        int age,
        string contact
    );


    int addDoctor(
        string name,
        Department dept
    );


    // =====================================================
    // PATIENT ADMISSION
    // =====================================================

    void admitPatient(
        int patientId,
        RoomType type
    );


    // =====================================================
    // NORMAL EMERGENCY
    // =====================================================

    void addEmergency(
        int patientId
    );


    int handleEmergency();


    // =====================================================
    // APPOINTMENTS
    // =====================================================

    void bookAppointment(
        int doctorId,
        int patientId
    );


    // =====================================================
    // BASIC INFORMATION DISPLAY
    // =====================================================

    void displayPatientInfo(
        int patientId
    );


    void displayDoctorInfo(
        int doctorId
    );


    // =====================================================
    // FIND PATIENT
    // =====================================================

    Patient* findPatient(
        int patientId
    );


    // =====================================================
    // FIND DOCTOR
    // =====================================================

    Doctor* findDoctor(
        int doctorId
    );


    // =====================================================
    // ==================== STORY 5 ========================
    // =====================================================
    // HOSPITAL ADVANCED FEATURES
    // SEARCH PATIENT
    // DISCHARGE
    // MEDICAL TESTS
    // PRESCRIPTIONS
    // BILLING
    // PRIORITY EMERGENCY
    // ROOM MANAGEMENT
    // =====================================================


    // =====================================================
    // SEARCH PATIENT BY NAME
    // =====================================================

    void searchPatientByName(string name)
{
    bool found = false;

    for (Patient &p : patients)
    {
        if (p.getName() == name)
        {
            cout << "Patient Found:" << endl;
            cout << "ID: " << p.getId() << endl;
            cout << "Name: " << p.getName() << endl;
            cout << "Age: " << p.getAge() << endl;
            cout << "Contact: " << p.getContact() << endl;
            cout << "Admission Status: "
                 << (p.getAdmissionStatus() ? "Admitted" : "Not Admitted")
                 << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "Patient not found." << endl;
    }
}


    // =====================================================
    // DISCHARGE PATIENT
    // =====================================================

    void dischargePatient(int patientId)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            patients[i].dischargePatient();

            cout << "Patient discharged successfully.\n";
            return;
        }
    }

    cout << "Patient not found.\n";
}


    // =====================================================
    // REQUEST MEDICAL TEST
    // =====================================================

    void requestPatientTest(int patientId, string testName)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            patients[i].requestTest(testName);

            cout << "Test requested successfully.\n";
            return;
        }
    }

    cout << "Patient not found.\n";
}


    // =====================================================
    // PERFORM MEDICAL TEST
    // =====================================================

    void performPatientTest(int patientId)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            string test = patients[i].performTest();

            cout << "Performed Test: " << test << endl;
            return;
        }
    }

    cout << "Patient not found.\n";
}


    // =====================================================
    // DISPLAY PENDING TESTS
    // =====================================================

    void displayPatientTests(int patientId)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            patients[i].displayPendingTests();
            return;
        }
    }

    cout << "Patient not found.\n";
}

    // =====================================================
    // ADD PRESCRIPTION
    // =====================================================

    void prescribeMedicine(int patientId, string medicine)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            patients[i].addPrescription(medicine);

            cout << "Medicine prescribed successfully.\n";
            return;
        }
    }

    cout << "Patient not found.\n";
}


    // =====================================================
    // DISPLAY PRESCRIPTIONS
    // =====================================================

    void displayPrescriptions(int patientId)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            patients[i].displayPrescriptions();
            return;
        }
    }

    cout << "Patient not found.\n";
}

    // =====================================================
    // PATIENT BILL
    // =====================================================

    void displayPatientBill(int patientId)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].getId() == patientId)
        {
            cout << "Patient Bill: " << patients[i].getBill() << endl;
            return;
        }
    }

    cout << "Patient not found.\n";
}


    // =====================================================
    // PRIORITY EMERGENCY
    // =====================================================

    void addPriorityEmergency(int patientId, int severity)
{
    priorityEmergencyQueue.push(EmergencyCase(patientId, severity));

    cout << "Priority emergency added successfully.\n";
}


    // =====================================================
    // HANDLE PRIORITY EMERGENCY
    // =====================================================

    int handlePriorityEmergency()
{
    if (priorityEmergencyQueue.empty())
    {
        cout << "No emergency cases.\n";
        return -1;
    }

    int patientId =
        priorityEmergencyQueue.top().getPatientId();

    priorityEmergencyQueue.pop();

    return patientId;
}


    // =====================================================
    // ROOM AVAILABILITY
    // =====================================================

    bool isRoomAvailable(RoomType type)
{
    if (type == GENERAL_WARD)
        return generalRooms > 0;

    if (type == ICU)
        return icuRooms > 0;

    if (type == PRIVATE_ROOM)
        return privateRooms > 0;

    if (type == SEMI_PRIVATE)
        return semiPrivateRooms > 0;

    return false;
}


    // =====================================================
    // DISPLAY ROOM STATUS
    // =====================================================

    void displayRoomStatus()
{
    cout << "General Ward Rooms: " << generalRooms << endl;
    cout << "ICU Rooms: " << icuRooms << endl;
    cout << "Private Rooms: " << privateRooms << endl;
    cout << "Semi-Private Rooms: " << semiPrivateRooms << endl;
}


    // =====================================================
    // ==================== STORY 6 ========================
    // =====================================================
    // DISPLAY ALL PATIENTS
    // DISPLAY ALL DOCTORS
    // DOCTOR APPOINTMENTS
    // CANCEL APPOINTMENT
    // DOCTOR SEES PATIENT
    // HOSPITAL STATISTICS
    // MAIN PROGRAM / INTEGRATION TESTING
    // =====================================================


    // =====================================================
    // DISPLAY ALL PATIENTS
    // =====================================================

    void displayAllPatients();


    // =====================================================
    // DISPLAY ALL DOCTORS
    // =====================================================

    void displayAllDoctors();


    // =====================================================
    // DISPLAY DOCTOR APPOINTMENTS
    // =====================================================

    void displayDoctorAppointments(
        int doctorId
    );


    // =====================================================
    // CANCEL APPOINTMENT
    // =====================================================

    void cancelAppointment(
        int doctorId,
        int patientId
    );


    // =====================================================
    // DOCTOR SEES NEXT PATIENT
    // =====================================================

    void doctorSeePatient(
        int doctorId
    );


    // =====================================================
    // HOSPITAL STATISTICS
    // =====================================================

    void displayStatistics();
};


// =====================================================
// ==================== STORY 6 ========================
// =====================================================
// MAIN PROGRAM
// INTEGRATION TESTING
// ALL TEST CASES
// EDGE CASES
// =====================================================

int main() {

    Hospital hospital;


    // =====================================================
    // TEST CASE 1
    // Registering patients
    // =====================================================

    int p1 =
        hospital.registerPatient(
            "John Doe",
            35,
            "555-1234"
        );


    int p2 =
        hospital.registerPatient(
            "Jane Smith",
            28,
            "555-5678"
        );


    int p3 =
        hospital.registerPatient(
            "Mike Johnson",
            45,
            "555-9012"
        );


    // =====================================================
    // TEST CASE 2
    // Adding doctors
    // =====================================================

    int d1 =
        hospital.addDoctor(
            "Dr. Smith",
            CARDIOLOGY
        );


    int d2 =
        hospital.addDoctor(
            "Dr. Brown",
            NEUROLOGY
        );


    int d3 =
        hospital.addDoctor(
            "Dr. Lee",
            PEDIATRICS
        );


    // =====================================================
    // TEST CASE 3
    // Admitting patients
    // =====================================================

    hospital.admitPatient(
        p1,
        PRIVATE_ROOM
    );


    hospital.admitPatient(
        p2,
        ICU
    );


    // Try admitting already admitted patient

    hospital.admitPatient(
        p1,
        SEMI_PRIVATE
    );


    // =====================================================
    // TEST CASE 4
    // Booking appointments
    // =====================================================

    hospital.bookAppointment(
        d1,
        p1
    );


    hospital.bookAppointment(
        d1,
        p2
    );


    hospital.bookAppointment(
        d2,
        p3
    );


    // Invalid doctor

    hospital.bookAppointment(
        999,
        p1
    );


    // Invalid patient

    hospital.bookAppointment(
        d1,
        999
    );


    // =====================================================
    // TEST CASE 5
    // Handling medical tests
    // =====================================================

    hospital.requestPatientTest(
        p1,
        "Blood Test"
    );


    hospital.requestPatientTest(
        p1,
        "X-Ray"
    );


    hospital.requestPatientTest(
        p1,
        "MRI"
    );


    hospital.displayPatientTests(
        p1
    );


    hospital.performPatientTest(
        p1
    );


    hospital.displayPatientTests(
        p1
    );


    // =====================================================
    // TEST CASE 6
    // Emergency cases
    // =====================================================

    hospital.addEmergency(p3);

    hospital.addEmergency(p1);


    int emergencyPatient =
        hospital.handleEmergency();


    emergencyPatient =
        hospital.handleEmergency();


    emergencyPatient =
        hospital.handleEmergency();


    // No more emergencies


    // =====================================================
    // TEST CASE 7
    // Discharging patients
    // =====================================================

    hospital.dischargePatient(
        p1
    );


    // =====================================================
    // TEST CASE 8
    // Displaying information
    // =====================================================

    hospital.displayPatientInfo(
        p1
    );


    hospital.displayPatientInfo(
        p2
    );


    hospital.displayPatientInfo(
        999
    );


    hospital.displayDoctorInfo(
        d1
    );


    hospital.displayDoctorInfo(
        d2
    );


    hospital.displayDoctorInfo(
        999
    );


    // =====================================================
    // TEST CASE 9
    // Doctor seeing patients
    // =====================================================

    hospital.displayDoctorAppointments(
        d1
    );


    hospital.doctorSeePatient(
        d1
    );


    hospital.displayDoctorAppointments(
        d1
    );


    // =====================================================
    // TEST CASE 10
    // Search Patient
    // =====================================================

    hospital.searchPatientByName(
        "John Doe"
    );


    hospital.searchPatientByName(
        "Unknown Patient"
    );


    // =====================================================
    // TEST CASE 11
    // Prescriptions
    // =====================================================

    hospital.prescribeMedicine(
        p1,
        "Paracetamol"
    );


    hospital.prescribeMedicine(
        p1,
        "Antibiotic"
    );


    hospital.displayPrescriptions(
        p1
    );


    // =====================================================
    // TEST CASE 12
    // Patient Billing
    // =====================================================

    hospital.displayPatientBill(
        p1
    );


    hospital.displayPatientBill(
        p2
    );


    // =====================================================
    // TEST CASE 13
    // Priority Emergency
    // =====================================================

    hospital.addPriorityEmergency(
        p1,
        2
    );


    hospital.addPriorityEmergency(
        p2,
        5
    );


    hospital.addPriorityEmergency(
        p3,
        3
    );


    hospital.addPriorityEmergency(
        p1,
        4
    );


    // =====================================================
    // TEST CASE 14
    // Handle Priority Emergencies
    // =====================================================

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();


    // =====================================================
    // TEST CASE 15
    // Room Management
    // =====================================================

    hospital.displayRoomStatus();


    // =====================================================
    // TEST CASE 16
    // Display All Patients
    // =====================================================

    hospital.displayAllPatients();


    // =====================================================
    // TEST CASE 17
    // Display All Doctors
    // =====================================================

    hospital.displayAllDoctors();


    // =====================================================
    // TEST CASE 18
    // Cancel Appointment
    // =====================================================

    hospital.cancelAppointment(
        d1,
        p2
    );


    // =====================================================
    // TEST CASE 19
    // More Doctor Appointments
    // =====================================================

    hospital.displayDoctorAppointments(
        d1
    );


    hospital.displayDoctorAppointments(
        d2
    );


    // =====================================================
    // TEST CASE 20
    // Hospital Statistics
    // =====================================================

    hospital.displayStatistics();


    // =====================================================
    // TEST CASE 21
    // Edge Cases
    // =====================================================

    Hospital emptyHospital;


    emptyHospital.displayPatientInfo(
        1
    );


    emptyHospital.displayDoctorInfo(
        1
    );


    emptyHospital.handleEmergency();


    emptyHospital.handlePriorityEmergency();


    emptyHospital.searchPatientByName(
        "John Doe"
    );


    emptyHospital.displayAllPatients();


    emptyHospital.displayAllDoctors();


    emptyHospital.displayStatistics();


    return 0;
}
