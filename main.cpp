#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// =====================================================
// ==================== ENUMERATIONS ====================
// =====================================================

enum Department
{
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType
{
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// =====================================================
// ================= EMERGENCY CASE =====================
// =====================================================

class EmergencyCase
{
private:
    int patientId;
    int severity;

public:
    EmergencyCase(int pid, int s)
    {
        patientId = pid;
        severity = s;
    }

    int getPatientId() const
    {
        return patientId;
    }

    int getSeverity() const
    {
        return severity;
    }

    // Higher severity = higher priority
    bool operator<(const EmergencyCase& other) const
    {
        return severity < other.severity;
    }
};

// =====================================================
// ==================== PATIENT =========================
// =====================================================

class Patient
{
private:
    int id;
    string name;
    int age;
    string contact;

    // LIFO medical history
    stack<string> medicalHistory;

    // FIFO diagnostic tests
    queue<string> testQueue;

    // Prescriptions in insertion order
    vector<string> prescriptions;

    bool isAdmitted;
    RoomType roomType;

    // Running bill
    double bill;

public:

    // =================================================
    // Constructor
    // =================================================

    Patient(int pid, string n, int a, string c)
    {
        id = pid;
        name = n;
        age = a;
        contact = c;

        isAdmitted = false;
        bill = 0;
    }

    // =================================================
    // Admission
    // =================================================

    bool admitPatient(RoomType type)
    {
        if (isAdmitted)
        {
            cout << "Patient is already admitted." << endl;
            return false;
        }

        isAdmitted = true;
        roomType = type;

        addMedicalRecord("Patient admitted to hospital");

        switch (type)
        {
        case GENERAL_WARD:
            bill += 500;
            break;

        case ICU:
            bill += 3000;
            break;

        case PRIVATE_ROOM:
            bill += 1500;
            break;

        case SEMI_PRIVATE:
            bill += 1000;
            break;
        }

        return true;
    }

    // =================================================
    // Discharge
    // =================================================

    bool dischargePatient()
    {
        if (!isAdmitted)
        {
            cout << "Patient is not currently admitted." << endl;
            return false;
        }

        isAdmitted = false;

        addMedicalRecord("Patient discharged from hospital");

        return true;
    }

    // =================================================
    // Medical History
    // =================================================

    void addMedicalRecord(const string& record)
    {
        medicalHistory.push(record);
    }

    void displayHistory() const
    {
        cout << "Medical History for "
            << name
            << " (ID: "
            << id
            << "):"
            << endl;

        stack<string> temp = medicalHistory;

        while (!temp.empty())
        {
            cout << "- " << temp.top() << endl;
            temp.pop();
        }
    }

    // =================================================
    // Medical Tests
    // =================================================

    void requestTest(const string& testName)
    {
        testQueue.push(testName);

        addMedicalRecord("Test requested: " + testName);
    }

    string performTest()
    {
        if (testQueue.empty())
        {
            return "No tests pending";
        }

        string testName = testQueue.front();

        testQueue.pop();

        addMedicalRecord("Test performed: " + testName);

        // Each performed test = $300
        bill += 300;

        return testName;
    }

    void displayPendingTests() const
    {
        if (testQueue.empty())
        {
            cout << "No pending tests." << endl;
            return;
        }

        cout << "Pending Tests:" << endl;

        queue<string> temp = testQueue;

        while (!temp.empty())
        {
            cout << "- " << temp.front() << endl;
            temp.pop();
        }
    }

    // =================================================
    // Prescriptions
    // =================================================

    void addPrescription(const string& medicine)
    {
        prescriptions.push_back(medicine);

        addMedicalRecord(
            "Prescription added: " + medicine
        );

        // Each prescription = $100
        bill += 100;
    }

    void displayPrescriptions() const
    {
        if (prescriptions.empty())
        {
            cout << "No prescriptions." << endl;
            return;
        }

        cout << "Prescriptions:" << endl;

        for (const string& medicine : prescriptions)
        {
            cout << "- " << medicine << endl;
        }
    }

    // =================================================
    // Billing
    // =================================================

    void addBill(double amount)
    {
        bill += amount;
    }

    double getBill() const
    {
        return bill;
    }

    void displayBill() const
    {
        cout << "========== PATIENT BILL ==========" << endl;

        cout << "Patient ID: "
            << id
            << endl;

        cout << "Patient Name: "
            << name
            << endl;

        cout << "Total Bill: $"
            << bill
            << endl;

        cout << "==================================" << endl;
    }

    // =================================================
    // Getters
    // =================================================

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    string getContact() const
    {
        return contact;
    }

    bool getAdmissionStatus() const
    {
        return isAdmitted;
    }

    RoomType getRoomType() const
    {
        return roomType;
    }
};

// =====================================================
// ====================== DOCTOR ========================
// =====================================================

class Doctor
{
private:
    int id;
    string name;
    Department department;

    // FIFO appointment queue
    queue<int> appointmentQueue;

public:

    // =================================================
    // Constructor
    // =================================================

    Doctor(int did, string n, Department d)
    {
        id = did;
        name = n;
        department = d;
    }

    // =================================================
    // Department Name
    // =================================================

    static string departmentName(Department d)
    {
        switch (d)
        {
        case CARDIOLOGY:
            return "Cardiology";

        case NEUROLOGY:
            return "Neurology";

        case ORTHOPEDICS:
            return "Orthopedics";

        case PEDIATRICS:
            return "Pediatrics";

        case EMERGENCY:
            return "Emergency";

        case GENERAL:
            return "General";
        }

        return "Unknown";
    }

    // =================================================
    // Appointment Management
    // =================================================

    void addAppointment(int patientId)
    {
        appointmentQueue.push(patientId);
    }

    int seePatient()
    {
        if (appointmentQueue.empty())
        {
            return -1;
        }

        int patientId = appointmentQueue.front();

        appointmentQueue.pop();

        return patientId;
    }

    void cancelAppointment(int patientId)
    {
        if (appointmentQueue.empty())
        {
            cout << "No appointments available." << endl;
            return;
        }

        queue<int> temp;

        bool found = false;

        while (!appointmentQueue.empty())
        {
            int currentPatientId =
                appointmentQueue.front();

            appointmentQueue.pop();

            // Remove only first occurrence
            if (currentPatientId == patientId && !found)
            {
                found = true;
                continue;
            }

            temp.push(currentPatientId);
        }

        appointmentQueue = temp;

        if (found)
        {
            cout << "Appointment cancelled successfully."
                << endl;
        }
        else
        {
            cout << "Appointment not found."
                << endl;
        }
    }

    void displayAppointments() const
    {
        if (appointmentQueue.empty())
        {
            cout << "No appointments." << endl;
            return;
        }

        cout << "Appointment Queue:" << endl;

        queue<int> temp = appointmentQueue;

        while (!temp.empty())
        {
            cout << "- Patient ID: "
                << temp.front()
                << endl;

            temp.pop();
        }
    }

    // =================================================
    // Getters
    // =================================================

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getDepartment() const
    {
        return departmentName(department);
    }

    int getAppointmentCount() const
    {
        return static_cast<int>(
            appointmentQueue.size()
            );
    }
};

// =====================================================
// ====================== HOSPITAL ======================
// =====================================================

class Hospital
{
private:

    vector<Patient> patients;
    vector<Doctor> doctors;

    // Standard FIFO emergency queue
    queue<int> emergencyQueue;

    // Severity-based emergency queue
    priority_queue<EmergencyCase>
        priorityEmergencyQueue;

    int patientCounter;
    int doctorCounter;

    // Room inventory
    int generalRooms;
    int icuRooms;
    int privateRooms;
    int semiPrivateRooms;

public:

    // =================================================
    // Constructor
    // =================================================

    Hospital()
    {
        patientCounter = 1;
        doctorCounter = 1;

        generalRooms = 20;
        icuRooms = 5;
        privateRooms = 10;
        semiPrivateRooms = 10;
    }

    // =================================================
    // Patient Registration
    // =================================================

    int registerPatient(
        const string& name,
        int age,
        const string& contact)
    {
        Patient newPatient(
            patientCounter,
            name,
            age,
            contact
        );

        patients.push_back(newPatient);

        return patientCounter++;
    }

    // =================================================
    // Doctor Registration
    // =================================================

    int addDoctor(
        const string& name,
        Department dept)
    {
        Doctor newDoctor(
            doctorCounter,
            name,
            dept
        );

        doctors.push_back(newDoctor);

        return doctorCounter++;
    }

    // =================================================
    // Find Patient
    // =================================================

    Patient* findPatient(int patientId)
    {
        for (Patient& patient : patients)
        {
            if (patient.getId() == patientId)
            {
                return &patient;
            }
        }

        return nullptr;
    }

    // =================================================
    // Find Doctor
    // =================================================

    Doctor* findDoctor(int doctorId)
    {
        for (Doctor& doctor : doctors)
        {
            if (doctor.getId() == doctorId)
            {
                return &doctor;
            }
        }

        return nullptr;
    }

    // =================================================
    // Room Availability
    // =================================================

    bool isRoomAvailable(RoomType type) const
    {
        switch (type)
        {
        case GENERAL_WARD:
            return generalRooms > 0;

        case ICU:
            return icuRooms > 0;

        case PRIVATE_ROOM:
            return privateRooms > 0;

        case SEMI_PRIVATE:
            return semiPrivateRooms > 0;
        }

        return false;
    }

    // =================================================
    // Admit Patient
    // =================================================

    void admitPatient(
        int patientId,
        RoomType type)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient with ID "
                << patientId
                << " not found."
                << endl;

            return;
        }

        if (patient->getAdmissionStatus())
        {
            cout << "Patient is already admitted."
                << endl;

            return;
        }

        if (!isRoomAvailable(type))
        {
            cout << "No room available for this room type."
                << endl;

            return;
        }

        /*
            IMPORTANT:
            According to SRS v2.0, room counters are
            checked for availability but are NOT
            decremented after admission.
        */

        patient->admitPatient(type);
    }

    // =================================================
    // Discharge Patient
    // =================================================

    void dischargePatient(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        if (patient->dischargePatient())
        {
            cout << "Patient discharged successfully."
                << endl;
        }
    }

    // =================================================
    // Standard Emergency FIFO
    // =================================================

    void addEmergency(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient with ID "
                << patientId
                << " not found."
                << endl;

            return;
        }

        emergencyQueue.push(patientId);
    }

    int handleEmergency()
    {
        if (emergencyQueue.empty())
        {
            cout << "No emergencies in queue."
                << endl;

            return -1;
        }

        int patientId =
            emergencyQueue.front();

        emergencyQueue.pop();

        cout << "Handled emergency for patient: "
            << patientId
            << endl;

        return patientId;
    }

    // =================================================
    // Appointments
    // =================================================

    void bookAppointment(
        int doctorId,
        int patientId)
    {
        Doctor* doctor =
            findDoctor(doctorId);

        Patient* patient =
            findPatient(patientId);

        // Report doctor error if needed
        if (doctor == nullptr)
        {
            cout << "Doctor with ID "
                << doctorId
                << " not found."
                << endl;
        }

        // Report patient error if needed
        if (patient == nullptr)
        {
            cout << "Patient with ID "
                << patientId
                << " not found."
                << endl;
        }

        // Do not book if either is invalid
        if (doctor == nullptr ||
            patient == nullptr)
        {
            return;
        }

        doctor->addAppointment(patientId);

        cout << "Appointment booked for patient "
            << patientId
            << " with doctor "
            << doctorId
            << endl;
    }

    // =================================================
    // Cancel Appointment
    // =================================================

    void cancelAppointment(
        int doctorId,
        int patientId)
    {
        Doctor* doctor =
            findDoctor(doctorId);

        if (doctor == nullptr)
        {
            cout << "Doctor with ID "
                << doctorId
                << " not found."
                << endl;

            return;
        }

        doctor->cancelAppointment(patientId);
    }

    // =================================================
    // Doctor Sees Patient
    // =================================================

    void doctorSeePatient(int doctorId)
    {
        Doctor* doctor =
            findDoctor(doctorId);

        if (doctor == nullptr)
        {
            cout << "Doctor with ID "
                << doctorId
                << " not found."
                << endl;

            return;
        }

        int patientId =
            doctor->seePatient();

        if (patientId == -1)
        {
            cout << "No patients waiting."
                << endl;

            return;
        }

        cout << doctor->getName()
            << " is now seeing patient "
            << patientId
            << endl;
    }

    // =================================================
    // Display Doctor Appointments
    // =================================================

    void displayDoctorAppointments(
        int doctorId)
    {
        Doctor* doctor =
            findDoctor(doctorId);

        if (doctor == nullptr)
        {
            cout << "Doctor with ID "
                << doctorId
                << " not found."
                << endl;

            return;
        }

        cout << endl;

        cout << "Appointments for "
            << doctor->getName()
            << ":"
            << endl;

        doctor->displayAppointments();
    }

    // =================================================
    // Display Patient Information
    // =================================================

    void displayPatientInfo(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient with ID "
                << patientId
                << " not found."
                << endl;

            return;
        }

        cout << endl;

        cout << "Patient Information:"
            << endl;

        cout << "ID: "
            << patient->getId()
            << endl;

        cout << "Name: "
            << patient->getName()
            << endl;

        cout << "Admission Status: "
            << (patient->getAdmissionStatus()
                ? "Admitted"
                : "Not Admitted")
            << endl;

        patient->displayHistory();
    }

    // =================================================
    // Display Doctor Information
    // =================================================

    void displayDoctorInfo(int doctorId)
    {
        Doctor* doctor =
            findDoctor(doctorId);

        if (doctor == nullptr)
        {
            cout << "Doctor with ID "
                << doctorId
                << " not found."
                << endl;

            return;
        }

        cout << endl;

        cout << "Doctor Information:"
            << endl;

        cout << "ID: "
            << doctor->getId()
            << endl;

        cout << "Name: "
            << doctor->getName()
            << endl;

        cout << "Department: "
            << doctor->getDepartment()
            << endl;
    }

    // =================================================
    // Search Patient
    // =================================================

    void searchPatientByName(
        const string& name)
    {
        bool found = false;

        for (const Patient& patient : patients)
        {
            if (patient.getName() == name)
            {
                cout << "Patient Found:"
                    << endl;

                cout << "ID: "
                    << patient.getId()
                    << endl;

                cout << "Name: "
                    << patient.getName()
                    << endl;

                cout << "Age: "
                    << patient.getAge()
                    << endl;

                cout << "Contact: "
                    << patient.getContact()
                    << endl;

                found = true;
            }
        }

        if (!found)
        {
            cout << "Patient not found."
                << endl;
        }
    }

    // =================================================
    // Medical Tests
    // =================================================

    void requestPatientTest(
        int patientId,
        const string& testName)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        patient->requestTest(testName);

        cout << "Test requested successfully."
            << endl;
    }

    void performPatientTest(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        cout << "Test result/action: "
            << patient->performTest()
            << endl;
    }

    void displayPatientTests(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        patient->displayPendingTests();
    }

    // =================================================
    // Prescriptions
    // =================================================

    void prescribeMedicine(
        int patientId,
        const string& medicine)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        patient->addPrescription(medicine);

        cout << "Medicine prescribed successfully."
            << endl;
    }

    void displayPrescriptions(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        patient->displayPrescriptions();
    }

    // =================================================
    // Patient Bill
    // =================================================

    void displayPatientBill(int patientId)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found."
                << endl;

            return;
        }

        patient->displayBill();
    }

    // =================================================
    // Priority Emergency
    // =================================================

    void addPriorityEmergency(
        int patientId,
        int severity)
    {
        Patient* patient =
            findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient with ID "
                << patientId
                << " not found."
                << endl;

            return;
        }

        if (severity < 1 ||
            severity > 5)
        {
            cout << "Invalid severity. "
                << "Severity must be between 1 and 5."
                << endl;

            return;
        }

        priorityEmergencyQueue.push(
            EmergencyCase(
                patientId,
                severity
            )
        );

        cout << "Emergency added with severity "
            << severity
            << endl;
    }

    int handlePriorityEmergency()
    {
        if (priorityEmergencyQueue.empty())
        {
            cout << "No priority emergencies."
                << endl;

            return -1;
        }

        EmergencyCase current =
            priorityEmergencyQueue.top();

        priorityEmergencyQueue.pop();

        cout << "Handling patient "
            << current.getPatientId()
            << " with severity "
            << current.getSeverity()
            << endl;

        return current.getPatientId();
    }

    // =================================================
    // Room Status
    // =================================================

    void displayRoomStatus() const
    {
        cout << "========== ROOM STATUS =========="
            << endl;

        cout << "General Ward: "
            << generalRooms
            << endl;

        cout << "ICU: "
            << icuRooms
            << endl;

        cout << "Private Rooms: "
            << privateRooms
            << endl;

        cout << "Semi Private Rooms: "
            << semiPrivateRooms
            << endl;

        cout << "================================="
            << endl;
    }

    // =================================================
    // Display All Patients
    // =================================================

    void displayAllPatients() const
    {
        cout << endl;

        cout << "========== ALL PATIENTS =========="
            << endl;

        if (patients.empty())
        {
            cout << "No patients registered."
                << endl;

            return;
        }

        for (const Patient& patient : patients)
        {
            cout << "ID: "
                << patient.getId()
                << " | Name: "
                << patient.getName()
                << " | Age: "
                << patient.getAge()
                << " | Status: "
                << (patient.getAdmissionStatus()
                    ? "Admitted"
                    : "Not Admitted")
                << endl;
        }
    }

    // =================================================
    // Display All Doctors
    // =================================================

    void displayAllDoctors() const
    {
        cout << endl;

        cout << "========== ALL DOCTORS =========="
            << endl;

        if (doctors.empty())
        {
            cout << "No doctors registered."
                << endl;

            return;
        }

        for (const Doctor& doctor : doctors)
        {
            cout << "ID: "
                << doctor.getId()
                << " | Name: "
                << doctor.getName()
                << " | Department: "
                << doctor.getDepartment()
                << " | Appointments: "
                << doctor.getAppointmentCount()
                << endl;
        }
    }

    // =================================================
    // Hospital Statistics
    // =================================================

    void displayStatistics() const
    {
        int admittedPatients = 0;

        double totalBills = 0;

        for (const Patient& patient : patients)
        {
            if (patient.getAdmissionStatus())
            {
                admittedPatients++;
            }

            totalBills += patient.getBill();
        }

        cout << endl;

        cout << "========== HOSPITAL STATISTICS =========="
            << endl;

        cout << "Total Patients: "
            << patients.size()
            << endl;

        cout << "Total Doctors: "
            << doctors.size()
            << endl;

        cout << "Admitted Patients: "
            << admittedPatients
            << endl;

        cout << "Waiting Emergencies: "
            << emergencyQueue.size()
            << endl;

        cout << "Priority Emergencies: "
            << priorityEmergencyQueue.size()
            << endl;

        cout << "Total Generated Bills: $"
            << totalBills
            << endl;

        cout << "========================================="
            << endl;
    }
};

// =====================================================
// ======================== MAIN ========================
// =====================================================

int main()
{
    Hospital hospital;

    // =====================================================
    // TEST CASE 1 - Registering Patients
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
    // TEST CASE 2 - Adding Doctors
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

    (void)d3;

    // =====================================================
    // TEST CASE 3 - Admission
    // =====================================================

    hospital.admitPatient(
        p1,
        PRIVATE_ROOM
    );

    hospital.admitPatient(
        p2,
        ICU
    );

    // Edge case:
    // Already admitted patient
    hospital.admitPatient(
        p1,
        SEMI_PRIVATE
    );

    // =====================================================
    // TEST CASE 4 - Appointments
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
    // TEST CASE 5 - Standard Emergency FIFO
    // =====================================================

    hospital.addEmergency(p3);

    hospital.addEmergency(p1);

    hospital.handleEmergency();

    hospital.handleEmergency();

    // Empty queue edge case
    hospital.handleEmergency();

    // =====================================================
    // TEST CASE 6 - Patient Information
    // =====================================================

    hospital.displayPatientInfo(p1);

    hospital.displayPatientInfo(p2);

    // Invalid patient
    hospital.displayPatientInfo(999);

    // =====================================================
    // TEST CASE 7 - Doctor Information
    // =====================================================

    hospital.displayDoctorInfo(d1);

    hospital.displayDoctorInfo(d2);

    // Invalid doctor
    hospital.displayDoctorInfo(999);

    // =====================================================
    // TEST CASE 8 - Search Patient
    // =====================================================

    hospital.searchPatientByName(
        "John Doe"
    );

    hospital.searchPatientByName(
        "Unknown Patient"
    );

    // =====================================================
    // TEST CASE 9 - Medical Tests
    // =====================================================

    cout << "========== NEW FEATURES =========="
        << endl;

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

    cout << "Pending tests:"
        << endl;

    hospital.displayPatientTests(p1);

    cout << "Performing first test:"
        << endl;

    hospital.performPatientTest(p1);

    cout << "Remaining tests:"
        << endl;

    hospital.displayPatientTests(p1);

    // =====================================================
    // TEST CASE 10 - Prescriptions
    // =====================================================

    hospital.prescribeMedicine(
        p1,
        "Paracetamol"
    );

    hospital.prescribeMedicine(
        p1,
        "Antibiotic"
    );

    hospital.displayPrescriptions(p1);

    // =====================================================
    // TEST CASE 11 - Billing
    // =====================================================

    hospital.displayPatientBill(p1);

    hospital.displayPatientBill(p2);

    // =====================================================
    // TEST CASE 12 - Doctor Appointments
    // =====================================================

    hospital.displayDoctorAppointments(d1);

    hospital.displayDoctorAppointments(d2);

    hospital.doctorSeePatient(d1);

    hospital.displayDoctorAppointments(d1);

    // =====================================================
    // TEST CASE 13 - Cancel Appointment
    // =====================================================

    hospital.cancelAppointment(
        d1,
        p2
    );

    hospital.displayDoctorAppointments(d1);

    // =====================================================
    // TEST CASE 14 - Priority Emergencies
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

    cout << endl;

    cout << "Handling priority emergencies:"
        << endl;

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    // =====================================================
    // TEST CASE 15 - Room Status
    // =====================================================

    hospital.displayRoomStatus();

    // =====================================================
    // TEST CASE 16 - All Patients
    // =====================================================

    hospital.displayAllPatients();

    // =====================================================
    // TEST CASE 17 - All Doctors
    // =====================================================

    hospital.displayAllDoctors();

    // =====================================================
    // TEST CASE 18 - Discharge
    // =====================================================

    hospital.dischargePatient(p1);

    // =====================================================
    // TEST CASE 19 - Patient Information After Discharge
    // =====================================================

    hospital.displayPatientInfo(p1);

    // =====================================================
    // TEST CASE 20 - Hospital Statistics
    // =====================================================

    hospital.displayStatistics();

    // =====================================================
    // TEST CASE 21 - Final Patient Bills
    // =====================================================

    cout << endl;

    cout << "Final Patient Bills:"
        << endl;

    hospital.displayPatientBill(p1);

    hospital.displayPatientBill(p2);

    hospital.displayPatientBill(p3);

    // =====================================================
    // TEST CASE 22 - Empty Hospital Edge Cases
    // =====================================================

    Hospital emptyHospital;

    emptyHospital.displayPatientInfo(1);

    emptyHospital.displayDoctorInfo(1);

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