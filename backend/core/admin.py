from django.contrib import admin
from django import forms

from core import models


class HospitalDepartmentForm(forms.ModelForm):
    class Meta:
        model = models.HospitalDepartment
        exclude = ()

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.fields['department'].queryset = models.Department.objects.all().order_by('name')


class HospitalDepartmentInline(admin.StackedInline):
    model = models.HospitalDepartment
    fields = ('department',)
    forms = HospitalDepartmentForm
    extra = 1


class HospitalBranchInline(admin.StackedInline):
    model = models.HospitalBranch
    extra = 1


@admin.register(models.Department)
class DepartmentAdmin(admin.ModelAdmin):
    list_display = ('id', 'name')


@admin.register(models.Hospital)
class HospitalAdmin(admin.ModelAdmin):
    inlines = [HospitalBranchInline, HospitalDepartmentInline]
    list_display = ('name', 'address', 'phone_number', 'country')
    search_fields = ('name', 'country')
