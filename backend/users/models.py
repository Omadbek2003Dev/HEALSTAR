from django.db import models
from django.contrib.auth.models import AbstractUser, BaseUserManager

from core.models import Department

USER_ROLES = (
    ('sys-admin', 'Sys Admin'),
    ('doctor', 'Doctor'),
    ('patient', 'Patient')
)


class CustomUserManager(BaseUserManager):
    def create_user(self, email, password=None, **extra_fields):
        if not email:
            raise ValueError("The Email field must be set")
        email = self.normalize_email(email)
        user = self.model(email=email, **extra_fields)
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_superuser(self, email, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)
        extra_fields.setdefault("is_active", True)
        return self.create_user(email, password, **extra_fields)


class User(AbstractUser):
    username = models.CharField(max_length=150, null=True, blank=True)
    email = models.EmailField(max_length=150, unique=True)
    role = models.CharField(max_length=50, choices=USER_ROLES, null=True, blank=True)
    address = models.CharField(max_length=200)
    phone_number = models.CharField(max_length=200)
    passport_id = models.CharField(max_length=50)
    logo = models.CharField(max_length=100)

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = []

    objects = CustomUserManager()

    def __str__(self):
        return f"{self.role}: {self.get_full_name()}"


class SystemAdmin(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)

    def __str__(self):
        return self.user.__str__()

    class Meta:
        db_table = 'system_admin'


class Doctor(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    doctor_id = models.CharField(max_length=15)
    department = models.ForeignKey(Department, related_name='doctors', on_delete=models.CASCADE)
    specialization = models.CharField(max_length=150)
    experience = models.PositiveIntegerField()
    qualification = models.CharField(max_length=150)

    def __str__(self):
        return self.user.__str__()

    class Meta:
        db_table = 'doctor'


class Patient(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    patient_id = models.CharField(max_length=15)
    position = models.CharField(max_length=100)

    def __str__(self):
        return self.user.__str__()

    class Meta:
        db_table = 'patient'
