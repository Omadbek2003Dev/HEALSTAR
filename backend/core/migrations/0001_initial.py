# Generated by Django 4.2.7 on 2023-12-09 13:25

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Department',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=100)),
                ('logo', models.CharField(max_length=150, null=True)),
            ],
            options={
                'db_table': 'department',
            },
        ),
        migrations.CreateModel(
            name='Hospital',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=100)),
                ('address', models.CharField(max_length=200)),
                ('phone_number', models.CharField(max_length=15)),
                ('country', models.CharField(max_length=100)),
                ('website', models.CharField(max_length=50)),
            ],
            options={
                'db_table': 'hospital',
            },
        ),
        migrations.CreateModel(
            name='HospitalDepartment',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('department', models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='core.department')),
                ('hospital', models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, related_name='departments', to='core.hospital')),
            ],
            options={
                'db_table': 'hospital_department',
            },
        ),
        migrations.CreateModel(
            name='HospitalBranch',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('region', models.CharField(max_length=100)),
                ('phone_number', models.CharField(max_length=15, null=True)),
                ('address', models.CharField(max_length=200)),
                ('hospital', models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='core.hospital')),
            ],
            options={
                'db_table': 'hospital_branch',
            },
        ),
    ]
