from django.contrib import admin

from users import models


@admin.register(models.User)
class UserAdmin(admin.ModelAdmin):
    pass


@admin.register(models.SystemAdmin)
class SystemAdmin(admin.ModelAdmin):
    pass


@admin.register(models.Doctor)
class Doctor(admin.ModelAdmin):
    pass


@admin.register(models.Patient)
class Patient(admin.ModelAdmin):
    pass
