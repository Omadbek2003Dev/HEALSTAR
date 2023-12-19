#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <http/http-api.h>
#include <json-c/json.h>

//Used variables
struct http serv;
// const char *admin_name = "admin";
// const char *admin_email = "admin@gmail.com";
// const char *admin_password = "adminadmin";
int user_authentication = 0;

//Doctor variables
char doctor_name[255];
char doctor_surname[255];
char doctor_id[255];
char doctor_specialization[255];
char doctor_qualification[255];
char doctor_address[255];
char doctor_phone[255];
char doctor_experience[255];
char doctor_hospitals[255];
char doctor_working_hours[255];
char doctor_email[255];
char doctor_password[255];
char doctor_confirm_password[255];
//Admin variables
char admin_email[255];
char admin_password[255];
char admin_confirm_password[255];
//Hospital variables
char hospital_name[255];
char hospital_address[255];
char hospital_phone[255];
char hospital_email[255];
char hospital_password[255];
char hospital_confirm_password[255];
//Appointment variables
char appointment_date[255];
char appointment_time[255];
char appointment_reason[255];
char appointment_doctor[255];
char appointment_patient[255];
char appointment_status[255];
//Prescription variables
char prescription_date[255];
char prescription_doctor[255];
char prescription_patient[255];
char prescription_medicine[255];
char prescription_dosage[255];
char prescription_duration[255];
char prescription_status[255];
//Report variables
char report_date[255];
char report_doctor[255];
char report_patient[255];
char report_description[255];
char report_status[255];
//Patient variables
char patient_name[255];
char patient_surname[255];
char patient_id[255];
char patient_working_position[255];
char patient_address[255];
char patient_phone[255];
char patient_email[255];
char patient_password[255];
char patient_confirm_password[255];

// Make all Widgets global
//Welcome Page
GtkWidget *welcomePageWindow;
GtkWidget *doctorButton;
GtkWidget *patientButton;
GtkBuilder *welcome_builder;
char *role = "patient";
GtkWindow *openWindow;

//Sign In Page
GtkWidget *signInPageWindow;
GtkWidget *createAccountButton;
GtkWidget *logInButton;
GtkWidget *backButtonSignInPage;
GtkBuilder *signIn_builder;

//Create Account Patient Page
GtkWidget *createAccountPagePatientWindow;
GtkWidget *createAccountPagePatientSurnameEntry;
GtkWidget *createAccountPagePatientNameEntry;
GtkWidget *createAccountPagePatientIDEntry;
GtkWidget *createAccountPagePatientWorkingPositionEntry;
GtkWidget *createAccountPagePatientAddressEntry;
GtkWidget *createAccountPagePatientPhoneNumberEntry;
GtkWidget *submitButtonCreateAccountPagePatient;
GtkWidget *backButtonCreateAccountPagePatient;
GtkBuilder *createAccountPagePatient_builder;

//Create Account Doctor Page
GtkWidget *createAccountPageDoctorWindow;
GtkWidget *createAccountPageDoctorSurnameEntry;
GtkWidget *createAccountPageDoctorNameEntry;
GtkWidget *createAccountPageDoctorIDEntry;
GtkWidget *createAccountPageDoctorSpecializationEntry;
GtkWidget *createAccountPageDoctorQualificationEntry;
GtkWidget *createAccountPageDoctorAddressEntry;
GtkWidget *createAccountPageDoctorPhoneNumberEntry;
GtkWidget *createAccountPageDoctorExperienceEntry;
GtkWidget *createAccountPageDoctorHospitalsEntry;
GtkWidget *createAccountPageDoctorWorkingHoursEntry;
GtkWidget *submitButtonCreateAccountPageDoctor;
GtkWidget *backButtonCreateAccountPageDoctor;
GtkBuilder *createAccountPageDoctor_builder;

// Registration Page
GtkWidget *registrationWindow;
GtkWidget *registrationIDLabel;
GtkWidget *registrationEmailEntry;
GtkWidget *registrationPasswordEntry;
GtkWidget *registrationConfirmPasswordEntry;
GtkWidget *submitButtonRegistration;
GtkWidget *backButtonRegistration;
GtkBuilder *registration_builder;

//Confirmation Page
GtkWidget *confirmationPageWindow;
GtkWidget *loginButtonConfirmationPage;
GtkWidget *backButtonConfirmationPage;
GtkBuilder *confirmationPage_builder;

//Rejection Page
GtkWidget *rejectionPageWindow;
GtkWidget *backButtonRejectionPage;
GtkBuilder *rejectionPage_builder;

// Log In Page
GtkWidget *loginPageWindow;
GtkWidget *usernameInput;
GtkWidget *passwordInput;
GtkWidget *submitButton;
GtkWidget *backButtonLoginPage;
GtkBuilder *logInPage_builder;

// Dashboard Page
GtkWidget *messagePageWindow;
GtkWidget *doctorsButtonMessage;
GtkWidget *hospitalsButtonMessage;
GtkWidget *homeButtonMessage;
GtkWidget *menuButtonMenuBarMessage;
GtkWidget *logoutButtonMessagePage;
GtkWidget *sendMessageButton;
GtkBuilder *dashboardPage_builder;

// Hospital Page
GtkWidget *doctorProfileWindow;
GtkBuilder *hospitalPage_builder;

// Categories Page
GtkWidget *mainPage;
GtkWidget *logoutButtonMainPage;
GtkWidget *messagesButtonMainPage;
GtkWidget *hospitalsButtonMainPage;
GtkWidget *internalMedicineButtonCategories;
GtkWidget *cardiologyButtonCategories;
GtkWidget *orthopedicButtonCategories;
GtkWidget *neurologyButtonCategories;
GtkWidget *oncologyButtonCategories;
GtkWidget *pediatricsButtonCategories;
GtkWidget *obstetricsAndGynecologyButtonCategories;
GtkWidget *psychiatryButtonCategories;
GtkWidget *logoutButtonMainPage;
GtkBuilder *categoriesPage_builder;

//Doctors Page
GtkWidget *doctorsPageClientWindow;
GtkWidget *logoutButtonDoctorsPageClient;
GtkWidget *homeButtonDoctorsPageClient;
GtkWidget *messagesButtonDoctorPageClient;
GtkWidget *hospitalsButtonDoctorsPageClient;
GtkBuilder *doctorsPage_builder;

//Search Page
GtkWidget *ListOfRegions;
GtkWidget *listStoreGlobalLocal;
GtkWidget *searchType;
GtkWidget *searchingPage;
GtkWidget *searchingWindow;
GtkWidget *mainButtons;
GtkBuilder *searchPage_Builder;

// Searching Hospital Page
GtkWidget *searchingPageResultsHOSPITALS;
GtkBuilder *searchingPageResultsHOSPITALS_Builder;


// Function prototypes till Login Page
void on_doctorButton_clicked(GtkWidget *widget, gpointer data);
void on_patientButton_clicked(GtkWidget *widget, gpointer data);
void on_backButtonSignInPage_clicked(GtkWidget *widget, gpointer data);
void on_logInButton_clicked(GtkWidget *widget, gpointer data);
void on_createAccountButton_clicked(GtkWidget *widget, gpointer data);
void on_createAccountButtonForDoctor(char *role);
void on_submitButtonCreateAccountPageDoctor_clicked(GtkWidget *widget, gpointer data);
void on_backButtonCreateAccountPageDoctor_clicked(GtkWidget *widget, gpointer data);
void on_createAccountButtonForPatient(char *role);
void on_submitButtonCreateAccountPagePatient_clicked(GtkWidget *widget, gpointer data);
void on_backButtonCreateAccountPagePatient_clicked(GtkWidget *widget, gpointer data);
void on_submitButtonRegistration_clicked(GtkWidget *widget, gpointer data);
void on_backButtonRegistration_clicked(GtkWidget *widget, gpointer data);
void on_submitButton_clicked(GtkWidget *widget, gpointer data);
void on_submitButtonRegistration_clicked(GtkWidget *widget, gpointer data);
void on_backButtonRejectionPage_clicked(GtkWidget *widget, gpointer data);
void on_logInButtonConfirmationPage_clicked(GtkWidget *widget, gpointer data);
void on_backButtonConfirmationPage_clicked(GtkWidget *widget, gpointer data);
void on_submitLoginButton_clicked(GtkWidget *widget, gpointer data);
void on_backButtonLoginPage_clicked(GtkWidget *widget, gpointer data);
// Function prototypes after Login Page
void on_doctorsButtonMessage_clicked(GtkWidget *widget, gpointer data);
void on_hospitalsButtonMessage_clicked(GtkWidget *widget, gpointer data);
void on_homeButtonMessage_clicked(GtkWidget *widget, gpointer data);
void on_menuButtonMenuBarMessage_clicked(GtkWidget *widget, gpointer data);
void on_logoutButtonMessagePage_clicked(GtkWidget *widget, gpointer data);
void on_sendMessageButton_clicked(GtkWidget *widget, gpointer data);
void show_Dashboard(char *role);
void show_Categories(char *role);
gboolean validate_non_empty(GtkWidget *entry, const gchar *entry_name);
gboolean validationDoctorRegistration();
gboolean validationPatientRegistration();
gboolean validationLogin();
void on_logoutButtonDoctorsPageClient_clicked(GtkWidget *widget, gpointer data);
void on_homeButtonDoctorsPageClient_clicked(GtkWidget *widget, gpointer data);
void on_messagesButtonDoctorPageClient_clicked(GtkWidget *widget, gpointer data);
void on_hospitalsButtonDoctorsPageClient_clicked(GtkWidget *widget, gpointer data);

// Function to generate unique IDs
char* generateID(char role) {
    static int doctorCounter = 1;
    static int patientCounter = 1;

    // Maximum number of digits in the ID
    int maxDigits = 7;

    // Allocate memory for the ID string
    char *id = (char*)malloc((maxDigits + 1) * sizeof(char));

    // Check the role and generate the ID accordingly
    if (role == 'doctor') {
        // Doctor ID
        sprintf(id, "D%07d", doctorCounter++);
    } else if (role == 'patient') {
        // Patient ID
        sprintf(id, "P%07d", patientCounter++);
    } else {
        // Invalid role
        free(id);
        return 1;
    }
    return id;
}

// ********************************** Welcome Page *********************************************
int main(int argc, char *argv[]) {
    if(argc < 3)
	{
		fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
		return 1;
	}

	http_init(&serv, argv[1], atoi(argv[2]));
	
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Import the UI from Glade
    welcome_builder = gtk_builder_new_from_file("welcome_page.glade");

    // Get all widgets
    welcomePageWindow = GTK_WIDGET(gtk_builder_get_object(welcome_builder, "welcomePageWindow"));
    doctorButton = GTK_WIDGET(gtk_builder_get_object(welcome_builder, "doctorButton"));
    patientButton = GTK_WIDGET(gtk_builder_get_object(welcome_builder, "patientButton"));

    // Connect the destroy signal of the window
    g_signal_connect(welcomePageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect all signals
    g_signal_connect(doctorButton, "clicked", G_CALLBACK(on_doctorButton_clicked), NULL);
    g_signal_connect(patientButton, "clicked", G_CALLBACK(on_patientButton_clicked), NULL);

    openWindow = welcomePageWindow;
    // Show the window
    gtk_widget_show(openWindow);

    // Start the main loop
    gtk_main();

    return 0;
}


// ********************************** Sign In Page *********************************************
void load_sign_in_page(char *role) {
    // Hide the welcome page
    gtk_widget_hide(openWindow);
    // Import the UI from Glade
    signIn_builder = gtk_builder_new_from_file("sign_in_page.glade");
    // Get all widgets
    signInPageWindow = GTK_WIDGET(gtk_builder_get_object(signIn_builder, "signInPageWindow"));
    createAccountButton = GTK_WIDGET(gtk_builder_get_object(signIn_builder, "createAccountButton"));
    logInButton = GTK_WIDGET(gtk_builder_get_object(signIn_builder, "logInButton"));
    backButtonSignInPage = GTK_WIDGET(gtk_builder_get_object(signIn_builder, "backButtonSignInPage"));
    // Connect the destroy signal of the window
    g_signal_connect(signInPageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Connect all signals
    g_signal_connect(createAccountButton, "clicked", G_CALLBACK(on_createAccountButton_clicked), NULL);
    g_signal_connect(logInButton, "clicked", G_CALLBACK(on_logInButton_clicked), NULL);
    g_signal_connect(backButtonSignInPage, "clicked", G_CALLBACK(on_backButtonSignInPage_clicked), NULL);
    // Show the sign in page
    openWindow = signInPageWindow;
    gtk_widget_show(openWindow);
}

void on_doctorButton_clicked(GtkWidget *widget, gpointer data) {
    role = "doctor";
    load_sign_in_page(role);
}

void on_patientButton_clicked(GtkWidget *widget, gpointer data) {
    role = "patient";
    load_sign_in_page(role);
}

void on_backButtonSignInPage_clicked(GtkWidget *widget, gpointer data) {
    // Hide the sign-in page
    gtk_widget_hide(openWindow);
    // Show the welcome page
    openWindow = welcomePageWindow;
    gtk_widget_show(openWindow);
    // Set the role to NULL
    role = NULL;
}

void on_createAccountButton_clicked(GtkWidget *widget, gpointer data) {
    if (strcmp(role, "doctor") == 0) {
        on_createAccountButtonForDoctor(role);
    } else if (strcmp(role, "patient") == 0) {
        on_createAccountButtonForPatient(role);
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_logInButton_clicked(GtkWidget *widget, gpointer data) {
    // Hide the sign-in page
    gtk_widget_hide(openWindow);
    // Import the UI from Glade
    logInPage_builder = gtk_builder_new_from_file("login_page.glade");
    // Get all widgets
    loginPageWindow = GTK_WIDGET(gtk_builder_get_object(logInPage_builder, "loginPageWindow"));
    usernameInput = GTK_WIDGET(gtk_builder_get_object(logInPage_builder, "usernameInput"));
    passwordInput = GTK_WIDGET(gtk_builder_get_object(logInPage_builder, "passwordInput"));
    submitButton = GTK_WIDGET(gtk_builder_get_object(logInPage_builder, "submitButton"));
    backButtonLoginPage = GTK_WIDGET(gtk_builder_get_object(logInPage_builder, "backButtonLoginPage"));  
    // Connect the destroy signal of the window
    g_signal_connect(loginPageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Connect all signals
    g_signal_connect(submitButton, "clicked", G_CALLBACK(on_submitLoginButton_clicked), NULL);
    g_signal_connect(backButtonLoginPage, "clicked", G_CALLBACK(on_backButtonLoginPage_clicked), NULL);
    // Show the Registration Page
    openWindow = loginPageWindow;
    gtk_widget_show(openWindow);
}


// ************************** Create Account For Doctor ************************************
void on_createAccountButtonForDoctor(char *role) {
    // Hide the sign-in page
    gtk_widget_hide(openWindow);
    // Import the UI from Glade
    createAccountPageDoctor_builder = gtk_builder_new_from_file("createAccountDoctor_page.glade");
    // Get all widgets
    createAccountPageDoctorWindow = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorWindow")); 
    createAccountPageDoctorSurnameEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorSurnameEntry"));
    createAccountPageDoctorNameEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorNameEntry"));
    createAccountPageDoctorIDEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorIDEntry"));
    createAccountPageDoctorSpecializationEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorSpecializationEntry"));
    createAccountPageDoctorQualificationEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorQualificationEntry"));
    createAccountPageDoctorAddressEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorAddressEntry"));
    createAccountPageDoctorPhoneNumberEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorPhoneNumberEntry"));
    createAccountPageDoctorExperienceEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorExperienceEntry"));
    createAccountPageDoctorHospitalsEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorHospitalsEntry"));
    createAccountPageDoctorWorkingHoursEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorWorkingHoursEntry"));
    submitButtonCreateAccountPageDoctor = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "submitButtonCreateAccountPageDoctor"));
    backButtonCreateAccountPageDoctor = GTK_WIDGET(gtk_builder_get_object(createAccountPageDoctor_builder, "backButtonCreateAccountPageDoctor"));
    // Connect the destroy signal of the window
    g_signal_connect(createAccountPageDoctorWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Connect all signals
    g_signal_connect(submitButtonCreateAccountPageDoctor, "clicked", G_CALLBACK(on_submitButtonCreateAccountPageDoctor_clicked), NULL);
    g_signal_connect(backButtonCreateAccountPageDoctor, "clicked", G_CALLBACK(on_backButtonCreateAccountPageDoctor_clicked), NULL);
    // Show the Create Account Page For Doctor
    openWindow = createAccountPageDoctorWindow;
    gtk_widget_show(openWindow);
}

void on_backButtonCreateAccountPageDoctor_clicked(GtkWidget *widget, gpointer data) {
    // Hide the create account page for doctor
    gtk_widget_hide(openWindow);
    // Show the sign in page
    openWindow = signInPageWindow;
    gtk_widget_show(openWindow);
    // Set the role to doctor
    role = "doctor";
}

void on_submitButtonCreateAccountPageDoctor_clicked(GtkWidget *widget, gpointer data) {
    if (!validationDoctorRegistration()) {
        return;
    }
    // Get the doctor ID
    role = "doctor";
    char *doctorID = generateID(role);
    strcpy(doctor_surname, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorSurnameEntry"))));
    strcpy(doctor_name, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorNameEntry"))));
    strcpy(doctor_id, doctorID);
    strcpy(doctor_specialization, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorSpecializationEntry"))));
    strcpy(doctor_qualification, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorQualificationEntry"))));
    strcpy(doctor_address, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorAddressEntry"))));
    strcpy(doctor_phone, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorPhoneNumberEntry"))));
    strcpy(doctor_experience, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorExperienceEntry"))));
    strcpy(doctor_hospitals, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorHospitalsEntry"))));
    strcpy(doctor_working_hours, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPageDoctor_builder, "createAccountPageDoctorWorkingHoursEntry"))));
    char *body_prepare = "\
    { \
        \"doctor_surname\": \"%s\", \
        \"doctor_name\": \"%s\", \
        \"doctor_id\": \"%s\", \
        \"doctor_specialization\": \"%s\", \
        \"doctor_qualification\": \"%s\", \
        \"doctor_address\": \"%s\", \
        \"doctor_phone\": \"%s\", \
        \"doctor_experience\": \"%s\", \
        \"doctor_hospitals\": \"%s\", \
        \"doctor_working_hours\": \"%s\", \
    }";
    char post_body[4096];
	sprintf(post_body, body_prepare, doctor_surname, doctor_name, doctor_id, doctor_specialization, doctor_qualification, doctor_address, doctor_phone, doctor_experience, doctor_hospitals, doctor_working_hours);
    char *response_body = NULL;
    int response_body_size = 0;

    //int ret_code = http_post(&serv, "/api/doctor/add", post_body, sizeof(post_body), &response_body, &response_body_size);
	int ret_code = 200;
	if(ret_code == 200)
	{	
        // Hide the sign-up page
        gtk_widget_hide(openWindow);
        // Import the Registration UI from Glade
        on_submitButton_clicked(widget, data);
    } else {
        // Validation for incorrect ret_code
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in request.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
//  Validation for Doctor Registration Page
gboolean validate_non_empty(GtkWidget *entry, const gchar *entry_name) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    if (g_utf8_strlen(text, -1) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "%s cannot be empty.", entry_name);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return FALSE;
    }
    return TRUE;
}

gboolean validationDoctorRegistration() {
    gboolean isSurnameValid = validate_non_empty(createAccountPageDoctorSurnameEntry, "Surname");
    gboolean isNameValid = validate_non_empty(createAccountPageDoctorNameEntry, "Name");
    // gboolean isIDValid = validate_non_empty(createAccountPageDoctorIDEntry, "ID");
    gboolean isSpecializationValid = validate_non_empty(createAccountPageDoctorSpecializationEntry, "Specialization");
    gboolean isQualificationValid = validate_non_empty(createAccountPageDoctorQualificationEntry, "Qualifation");
    gboolean isAddressValid = validate_non_empty(createAccountPageDoctorAddressEntry, "Address");
    gboolean isPhoneNumberValid = validate_non_empty(createAccountPageDoctorPhoneNumberEntry, "PhoneNumber");
    gboolean isExperienceValid = validate_non_empty(createAccountPageDoctorExperienceEntry, "Experience");
    gboolean isHospitalsValid = validate_non_empty(createAccountPageDoctorHospitalsEntry, "Hospitals");
    gboolean isWorkingHoursValid = validate_non_empty(createAccountPageDoctorWorkingHoursEntry, "WorkingHours");

    return isSurnameValid && isNameValid && isSpecializationValid && isQualificationValid && isAddressValid && isPhoneNumberValid && isExperienceValid && isHospitalsValid && isWorkingHoursValid;
}


// ************************** Create Account For Patient ************************************
void on_createAccountButtonForPatient(char *role) {
    // Hide the sign-in page
    gtk_widget_hide(openWindow);
    // Import the UI from Glade
    createAccountPagePatient_builder = gtk_builder_new_from_file("createAccountPatient_page.glade");
    // Get all widgets
    createAccountPagePatientWindow = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientWindow"));
    createAccountPagePatientSurnameEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientSurnameEntry"));
    createAccountPagePatientNameEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientNameEntry"));
    createAccountPagePatientIDEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientIDEntry"));
    createAccountPagePatientWorkingPositionEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientWorkingPositionEntry"));
    createAccountPagePatientAddressEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientAddressEntry"));
    createAccountPagePatientPhoneNumberEntry = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientPhoneNumberEntry"));
    submitButtonCreateAccountPagePatient = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "submitButtonCreateAccountPagePatient"));
    backButtonCreateAccountPagePatient = GTK_WIDGET(gtk_builder_get_object(createAccountPagePatient_builder, "backButtonCreateAccountPagePatient"));
    // Connect the destroy signal of the window
    g_signal_connect(createAccountPagePatientWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Connect all signals
    g_signal_connect(submitButtonCreateAccountPagePatient, "clicked", G_CALLBACK(on_submitButtonCreateAccountPagePatient_clicked), NULL);
    g_signal_connect(backButtonCreateAccountPagePatient, "clicked", G_CALLBACK(on_backButtonCreateAccountPagePatient_clicked), NULL);
    //Show the create account page for patient
    openWindow = createAccountPagePatientWindow;
    gtk_widget_show(openWindow);
}

void on_backButtonCreateAccountPagePatient_clicked(GtkWidget *widget, gpointer data) {
    // Hide the create account page
    gtk_widget_hide(openWindow);
    // Show the sign-in page
    openWindow = signInPageWindow;
    gtk_widget_show(openWindow);
    // Set the role to patient
    role = "patient";
}

void on_submitButtonCreateAccountPagePatient_clicked(GtkWidget *widget, gpointer data) {
    if (!validationPatientRegistration()) {
        return;
    }
    role = "patient";
    // Get the patient ID
    char *patientID = generateID(role);
    strcpy(patient_surname, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientSurnameEntry"))));
    strcpy(patient_name, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientNameEntry"))));
    strcpy(patient_id, patientID);
    strcpy(patient_working_position, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientWorkingPositionEntry"))));
    strcpy(patient_address, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientAddressEntry"))));
    strcpy(patient_phone, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(createAccountPagePatient_builder, "createAccountPagePatientPhoneNumberEntry"))));
    char *body_prepare = "\
    { \
        \"patient_surname\": \"%s\", \
        \"patient_name\": \"%s\", \
        \"patient_id\": \"%s\", \
        \"patient_working_position\": \"%s\", \
        \"patient_address\": \"%s\", \
        \"patient_phone\": \"%s\",  \
    }";
    char post_body[1024];
    sprintf(post_body, body_prepare, patient_surname, patient_name, patient_id, patient_working_position, patient_address, patient_phone);
    char *response_body = NULL;
    int response_body_size = 0;

    //int ret_code = http_post(&serv, "/api/patient/add", post_body, sizeof(post_body), &response_body, &response_body_size);
    int ret_code = 200;
    if(ret_code == 200)
    {	
        // Hide the sign-up page
        gtk_widget_hide(openWindow);
        // Import the Registration UI from Glade
        on_submitButton_clicked(widget, data);
    } else {
        // Validation for incorrect ret_code
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in request.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
// Validation for Patient Page
gboolean validationPatientRegistration() {
    gboolean isSurnameValid = validate_non_empty(createAccountPagePatientSurnameEntry, "Surname");
    gboolean isNameValid = validate_non_empty(createAccountPagePatientNameEntry, "Name");
    // gboolean isIDValid = validate_non_empty(createAccountPagePatientIDEntry, "ID");
    gboolean isWorkingPositionValid = validate_non_empty(createAccountPagePatientWorkingPositionEntry, "Working Position");
    gboolean isAddressValid = validate_non_empty(createAccountPagePatientAddressEntry, "Address");
    gboolean isPhoneNumberValid = validate_non_empty(createAccountPagePatientPhoneNumberEntry, "PhoneNumber");

    return isSurnameValid && isNameValid && isWorkingPositionValid && isAddressValid && isPhoneNumberValid;
}


// ********************************** Registration Page *********************************************
void on_submitButton_clicked(GtkWidget *widget, gpointer data) {
    // Import the UI from Glade
    registration_builder = gtk_builder_new_from_file("registration_page.glade");
    // Get all widgets
    registrationWindow = GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationWindow"));
    registrationIDLabel = GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationIDLabel"));
    if (strcmp(role, "doctor") == 0) {
        gtk_label_set_text(GTK_LABEL(registrationIDLabel), doctor_id);
    } else if (strcmp(role, "patient") == 0) {
        gtk_label_set_text(GTK_LABEL(registrationIDLabel), patient_id);
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    registrationEmailEntry = GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationEmailEntry"));
    registrationPasswordEntry = GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationPasswordEntry"));
    registrationConfirmPasswordEntry = GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationConfirmPasswordEntry"));
    submitButtonRegistration = GTK_WIDGET(gtk_builder_get_object(registration_builder, "submitButtonRegistration"));
    backButtonRegistration = GTK_WIDGET(gtk_builder_get_object(registration_builder, "backButtonRegistration"));
    // Connect the destroy signal of the window
    g_signal_connect(registrationWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Connect all signals
    g_signal_connect(submitButtonRegistration, "clicked", G_CALLBACK(on_submitButtonRegistration_clicked), NULL);
    g_signal_connect(backButtonRegistration, "clicked", G_CALLBACK(on_backButtonRegistration_clicked), NULL);
    // Show the Registration Page
    openWindow = registrationWindow;
    gtk_widget_show(openWindow);
}

void on_backButtonRegistration_clicked(GtkWidget *widget, gpointer data) {
    // Hide the registration page
    gtk_widget_hide(openWindow);
    if (strcmp(role, "doctor") == 0) {
        // Show the create account page for doctor
        openWindow = createAccountPageDoctorWindow;
        gtk_widget_show(openWindow);
    } else if (strcmp(role, "patient") == 0) {
        // Show the create account page for patient
        openWindow = createAccountPagePatientWindow;
        gtk_widget_show(openWindow);
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


// ********************************** Confirmation or Rejection Page *********************************************
void on_submitButtonRegistration_clicked(GtkWidget *widget, gpointer data) {
    // Hide the sign-in page
    gtk_widget_hide(openWindow);
    // Posting the data to the server
    if (strcmp(role, "doctor") == 0) {
        strcpy(doctor_email, gtk_entry_get_text(GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationEmailEntry"))));
        strcpy(doctor_password, gtk_entry_get_text(GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationPasswordEntry"))));
        strcpy(doctor_confirm_password, gtk_entry_get_text(GTK_WIDGET(gtk_builder_get_object(registration_builder, "registrationConfirmPasswordEntry"))));
        if (strcmp(doctor_password, doctor_confirm_password) != 0) {
            // Validation for password and confirm password
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Password and Confirm Password do not match.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        char *body_prepare = "\
        { \
            \"doctor_email\": \"%s\", \
            \"doctor_password\": \"%s\", \
        }";
        char post_body[1024];
        sprintf(post_body, body_prepare, doctor_email, doctor_password);
        char *response_body = NULL;
        int response_body_size = 0;

        //int ret_code = http_post(&serv, "/api/doctor/add/secured", post_body, sizeof(post_body), &response_body, &response_body_size);
        int ret_code = 200;
        if(ret_code == 200)
        {	
            if (strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorSurnameEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorNameEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorSpecializationEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorQualificationEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorAddressEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorPhoneNumberEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorExperienceEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorHospitalsEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPageDoctorWorkingHoursEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(registrationEmailEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(registrationPasswordEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(registrationConfirmPasswordEntry)), "") == 0) {
                user_authentication = 0;
                // Show the rejection page
                openWindow = rejectionPageWindow;
                gtk_widget_show(openWindow);
                // Import the UI from Glade
                rejectionPage_builder = gtk_builder_new_from_file("rejection_page.glade");
                // Get all widgets
                rejectionPageWindow = GTK_WIDGET(gtk_builder_get_object(rejectionPage_builder, "rejectionPageWindow"));
                backButtonRejectionPage = GTK_WIDGET(gtk_builder_get_object(rejectionPage_builder, "backButtonRejectionPage"));
                // Connect the destroy signal of the window
                g_signal_connect(rejectionPageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
                // Connect all signals
                g_signal_connect(backButtonRejectionPage, "clicked", G_CALLBACK(on_backButtonRejectionPage_clicked), NULL);
            } else {
                user_authentication = 1;
                // Show the confirmation page
                gtk_widget_show(confirmationPageWindow);
                // Import the UI from Glade
                confirmationPage_builder = gtk_builder_new_from_file("confirmation_page.glade");
                // Get all widgets
                confirmationPageWindow = GTK_WIDGET(gtk_builder_get_object(confirmationPage_builder, "confirmationPageWindow"));
                loginButtonConfirmationPage = GTK_WIDGET(gtk_builder_get_object(confirmationPage_builder, "loginButtonConfirmationPage"));
                backButtonConfirmationPage = GTK_WIDGET(gtk_builder_get_object(confirmationPage_builder, "backButtonConfirmationPage"));
                // Connect the destroy signal of the window
                g_signal_connect(confirmationPageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
                // Connect all signals
                g_signal_connect(loginButtonConfirmationPage, "clicked", G_CALLBACK(on_logInButtonConfirmationPage_clicked), NULL);
                g_signal_connect(backButtonConfirmationPage, "clicked", G_CALLBACK(on_backButtonConfirmationPage_clicked), NULL);
            }
        } else {
            // Validation for incorrect ret_code
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Error in request.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else if (strcmp(role, "patient") == 0) {
        strcpy(patient_email, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(registration_builder, "registrationEmailEntry"))));
        strcpy(patient_password, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(registration_builder, "registrationPasswordEntry"))));
        strcpy(patient_confirm_password, gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(registration_builder, "registrationConfirmPasswordEntry"))));
        if (strcmp(patient_password, patient_confirm_password) != 0) {
            // Validation for password and confirm password
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Password and Confirm Password do not match.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        char *body_prepare = "\
        { \
            \"patient_email\": \"%s\", \
            \"patient_password\": \"%s\", \
        }";
        char post_body[1024];
        sprintf(post_body, body_prepare, patient_email, patient_password);
        char *response_body = NULL;
        int response_body_size = 0;

        //int ret_code = http_post(&serv, "/api/patient/add/secured", post_body, sizeof(post_body), &response_body, &response_body_size);
        int ret_code = 200;
        if(ret_code == 200)
        {	
            if (strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPagePatientSurnameEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPagePatientNameEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPagePatientWorkingPositionEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPagePatientAddressEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(createAccountPagePatientPhoneNumberEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(registrationEmailEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(registrationPasswordEntry)), "") == 0 || strcmp(gtk_entry_get_text(GTK_ENTRY(registrationConfirmPasswordEntry)), "") == 0) {
                user_authentication = 0;
                // Show the rejection page
                openWindow = rejectionPageWindow;
                gtk_widget_show(openWindow);
                // Import the UI from Glade
                rejectionPage_builder = gtk_builder_new_from_file("rejection_page.glade");
                // Get all widgets
                rejectionPageWindow = GTK_WIDGET(gtk_builder_get_object(rejectionPage_builder, "rejectionPageWindow"));
                backButtonRejectionPage = GTK_WIDGET(gtk_builder_get_object(rejectionPage_builder, "backButtonRejectionPage"));
                // Connect the destroy signal of the window
                g_signal_connect(rejectionPageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
                // Connect all signals
                g_signal_connect(backButtonRejectionPage, "clicked", G_CALLBACK(on_backButtonRejectionPage_clicked), NULL);
            } else {
                user_authentication = 1;
                // Show the confirmation page
                openWindow = confirmationPageWindow;
                gtk_widget_show(openWindow);
                // Import the UI from Glade
                confirmationPage_builder = gtk_builder_new_from_file("confirmation_page.glade");
                // Get all widgets
                confirmationPageWindow = GTK_WIDGET(gtk_builder_get_object(confirmationPage_builder, "confirmationPageWindow"));
                loginButtonConfirmationPage = GTK_WIDGET(gtk_builder_get_object(confirmationPage_builder, "loginButtonConfirmationPage"));
                backButtonConfirmationPage = GTK_WIDGET(gtk_builder_get_object(confirmationPage_builder, "backButtonConfirmationPage"));
                // Connect the destroy signal of the window
                g_signal_connect(confirmationPageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
                // Connect all signals
                g_signal_connect(loginButtonConfirmationPage, "clicked", G_CALLBACK(on_logInButtonConfirmationPage_clicked), NULL);
                g_signal_connect(backButtonConfirmationPage, "clicked", G_CALLBACK(on_backButtonConfirmationPage_clicked), NULL);
            }
        } else {
            // Validation for incorrect ret_code
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Error in request.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Incorrect role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_backButtonRejectionPage_clicked(GtkWidget *widget, gpointer data) {
    // Hide the rejection page
    gtk_widget_hide(openWindow);
    if (strcmp(role, "doctor") == 0) {
        // Show the create account page for doctor
        openWindow = createAccountPageDoctorWindow;
        gtk_widget_show(openWindow);
    } else if (strcmp(role, "patient") == 0) {
        // Show the create account page for patient
        openWindow = createAccountPagePatientWindow;
        gtk_widget_show(openWindow);
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_backButtonConfirmationPage_clicked(GtkWidget *widget, gpointer data) {
    // Hide the confirmation page
    gtk_widget_hide(openWindow);
    if (strcmp(role, "doctor") == 0) {
        // Show the create account page for doctor
        openWindow = createAccountPageDoctorWindow;
        gtk_widget_show(openWindow);
    } else if (strcmp(role, "patient") == 0) {
        // Show the create account page for patient
        openWindow = createAccountPagePatientWindow;
        gtk_widget_show(openWindow);
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Error in role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_logInButtonConfirmationPage_clicked(GtkWidget *widget, gpointer data) {
    // Hide the confirmation page
    gtk_widget_hide(openWindow);
    // Show the sign-in page
    openWindow = signInPageWindow;
    gtk_widget_show(openWindow);
    // Set the role to NULL
    role = NULL;
}


// ********************************** Login Page *********************************************
gboolean validationLogin() {
    gboolean isUsernameValid = validate_non_empty(usernameInput, "Username");
    gboolean isPasswordValid = validate_non_empty(passwordInput, "Password");

    return isUsernameValid && isPasswordValid;
}

void on_backButtonLoginPage_clicked(GtkWidget *widget, gpointer data){
    // Hide the Log In Page 
    gtk_widget_hide(openWindow);
    // Show the Welcome Page
    openWindow = signInPageWindow;
    gtk_widget_show(signInPageWindow);
}

void on_submitLoginButton_clicked(GtkWidget *widget, gpointer data) {
    if (!validationLogin()) {
        return;
    }
    if (strcmp(role, "doctor") == 0) {
        show_Dashboard(role);
    } else if (strcmp(role, "patient") == 0) {
        show_Categories(role);
    } else {
        // Validation for incorrect role
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Incorrect role.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


// ********************************** Dashboard Page *********************************************
void show_Dashboard(char *role){
    // Hide the Log In Page
    gtk_widget_hide(openWindow);
    // Import UI from Glade
    dashboardPage_builder = gtk_builder_new_from_file("chatClientWithDoctor_page.glade");
    // Get all widgets
    messagePageWindow = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "messagePageWindow"));
    doctorsButtonMessage = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "doctorsButtonMessage"));
    hospitalsButtonMessage = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "hospitalsButtonMessage"));
    homeButtonMessage = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "homeButtonMessage"));
    menuButtonMenuBarMessage = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "menuButtonMenuBarMessage"));
    logoutButtonMessagePage = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "logoutButtonMesaagePane"));
    sendMessageButton = GTK_WIDGET(gtk_builder_get_object(dashboardPage_builder, "sendMessageButton"));
    // Connect the destroy signal of the window
    g_signal_connect(messagePageWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Connect all signals
    g_signal_connect(doctorsButtonMessage, "clicked", G_CALLBACK(on_doctorsButtonMessage_clicked), NULL);
    g_signal_connect(hospitalsButtonMessage, "clicked", G_CALLBACK(on_hospitalsButtonMessage_clicked), NULL);
    g_signal_connect(homeButtonMessage, "clicked", G_CALLBACK(on_homeButtonMessage_clicked), NULL);
    g_signal_connect(menuButtonMenuBarMessage, "clicked", G_CALLBACK(on_menuButtonMenuBarMessage_clicked), NULL);
    g_signal_connect(logoutButtonMessagePage, "clicked", G_CALLBACK(on_logoutButtonMessagePage_clicked), NULL);
    g_signal_connect(sendMessageButton, "clicked", G_CALLBACK(on_sendMessageButton_clicked), NULL);
    // Show the Dashboard page
    openWindow = messagePageWindow;
    gtk_widget_show(openWindow);
} 

void show_Categories(char *role){
    // Get ui from Glade
    categoriesPage_builder = gtk_builder_new_from_file("mainCategories_page.glade");
    mainPage = GTK_WIDGET(gtk_builder_get_object(categoriesPage_builder, "mainPage"));
    openWindow = mainPage;
    gtk_widget_show(openWindow);
}


void on_doctorsButtonMessage_clicked(GtkWidget *widget, gpointer data){
    // Show UI from Glade
    doctorsPage_builder = gtk_builder_new_from_file("doctorsForClient_page.glade");
    doctorsPageClientWindow = GTK_WIDGET(gtk_builder_get_object(doctorsPage_builder, "doctorsPageClientWindow"));
    logoutButtonDoctorsPageClient = GTK_WIDGET(gtk_builder_get_object(doctorsPage_builder, "logoutButtonDoctorsPageClient"));
    homeButtonDoctorsPageClient = GTK_WIDGET(gtk_builder_get_object(doctorsPage_builder, "doctorsPageClientMenuBarFixed"));
    messagesButtonDoctorPageClient = GTK_WIDGET(gtk_builder_get_object(doctorsPage_builder, "messagesButtonDoctorPageClient"));
    hospitalsButtonDoctorsPageClient = GTK_WIDGET(gtk_builder_get_object(doctorsPage_builder, "hospitalsButtonDoctorsPageClient"));
    // Connect signals 
    g_signal_connect(logoutButtonDoctorsPageClient, "clicked", G_CALLBACK(on_logoutButtonDoctorsPageClient_clicked), NULL);
    g_signal_connect(homeButtonDoctorsPageClient, "clicked", G_CALLBACK(on_homeButtonDoctorsPageClient_clicked), NULL);
    g_signal_connect(messagesButtonDoctorPageClient, "clicked", G_CALLBACK(on_messagesButtonDoctorPageClient_clicked), NULL);
    g_signal_connect(hospitalsButtonDoctorsPageClient, "clicked", G_CALLBACK(on_hospitalsButtonDoctorsPageClient_clicked), NULL);
    openWindow = doctorsPageClientWindow;
    gtk_widget_show(openWindow);
}

void on_logoutButtonDoctorsPageClient_clicked(GtkWidget *widget, gpointer data){
    // Hide the Doctors Page
    gtk_widget_hide(openWindow);
    // Show Dashboard Page
    openWindow = messagePageWindow;
    gtk_widget_show(openWindow);
}

void on_homeButtonDoctorsPageClient_clicked(GtkWidget *widget, gpointer data){
    gtk_widget_hide(doctorsPageClientWindow);
    // Show Dashboard Page
    openWindow = messagePageWindow;
    gtk_widget_show(openWindow);
}

void on_messagesButtonDoctorPageClient_clicked(GtkWidget *widget, gpointer data){
    gtk_widget_hide(openWindow);
    // Show Dashboard Page
    openWindow = messagePageWindow;
    gtk_widget_show(openWindow);
}

void on_hospitalsButtonDoctorsPageClient_clicked(GtkWidget *widget, gpointer data){
    gtk_widget_hide(openWindow);
    // Show Dashboard Page
    searchPage_Builder = gtk_builder_new_from_file("searching_page.glade");
    ListOfRegions = GTK_WIDGET(gtk_builder_get_object(searchPage_Builder, "ListOfRegions"));
    listStoreGlobalLocal = GTK_WIDGET(gtk_builder_get_object(searchPage_Builder, "listStoreGlobalLocal"));
    searchType = GTK_WIDGET(gtk_builder_get_object(searchPage_Builder, "searchType"));
    searchingPage= GTK_WIDGET(gtk_builder_get_object(searchPage_Builder, "searchingPage"));
    searchingWindow = GTK_WIDGET(gtk_builder_get_object(searchPage_Builder, "searchingWindow"));
    mainButtons = GTK_WIDGET(gtk_builder_get_object(searchPage_Builder, "mainButtons"));
    // Show the Searching Page
    openWindow = searchingPage;
    gtk_widget_show(openWindow);
}

void on_hospitalsButtonMessage_clicked(GtkWidget *widget, gpointer data){
    // Open UI from Glade 
    searchingPageResultsHOSPITALS_Builder = gtk_builder_new_from_file("searching_page.glade");
    searchingPageResultsHOSPITALS = GTK_WIDGET(gtk_builder_get_object(searchingPageResultsHOSPITALS_Builder, "searchingPageResultsHOSPITALS"));
    // SHow the Hospital Page
    openWindow = searchingPageResultsHOSPITALS;
    gtk_widget_show(openWindow);
}

void on_homeButtonMessage_clicked(GtkWidget *widget, gpointer data){
    // Hide Active Page
    gtk_widget_hide(openWindow);
    // Show Dashboard Page
    openWindow = messagePageWindow;
    gtk_widget_show(openWindow);
}

void on_menuButtonMenuBarMessage_clicked(GtkWidget *widget, gpointer data){

}

void on_logoutButtonMessagePage_clicked(GtkWidget *widget, gpointer data){
    // Hide Dashboard Page
    gtk_widget_hide(openWindow);
    // Show Welcome Page
    openWindow = welcomePageWindow;
    gtk_widget_show_all(openWindow);
}

void on_sendMessageButton_clicked(GtkWidget *widget, gpointer data){

}