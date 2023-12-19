from django.db import models


class Department(models.Model):
    name = models.CharField(max_length=100)
    logo = models.CharField(max_length=150, null=True)

    def __str__(self):
        return self.name

    class Meta:
        db_table = 'department'


class Hospital(models.Model):
    name = models.CharField(max_length=100)
    address = models.CharField(max_length=200)
    phone_number = models.CharField(max_length=15)
    country = models.CharField(max_length=100)
    website = models.CharField(max_length=50)

    def __str__(self):
        return self.name

    class Meta:
        db_table = 'hospital'


class HospitalDepartment(models.Model):
    hospital = models.ForeignKey(Hospital, on_delete=models.DO_NOTHING, related_name='departments')
    department = models.ForeignKey(Department, on_delete=models.DO_NOTHING)

    def __str__(self):
        return self.department.name

    class Meta:
        db_table = 'hospital_department'


class HospitalBranch(models.Model):
    hospital = models.ForeignKey(Hospital, on_delete=models.DO_NOTHING)
    region = models.CharField(max_length=100)
    phone_number = models.CharField(max_length=15, null=True)
    address = models.CharField(max_length=200)

    def __str__(self):
        return f'{self.hospital.name} branch in {self.region}'

    class Meta:
        db_table = 'hospital_branch'
