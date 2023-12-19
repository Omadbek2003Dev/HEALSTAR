from django.db import models

from users.models import User


class Chat(models.Model):
    patient = models.ForeignKey(User, on_delete=models.DO_NOTHING, related_name='patient_chat')
    doctor = models.ForeignKey(User, on_delete=models.DO_NOTHING, related_name='doctor_chat')

    def __str__(self):
        return f'Chat between Doctor {self.doctor.get_full_name()} and Patient {self.doctor.get_full_name()}'

    class Meta:
        db_table = 'chat'


class ChatHistory(models.Model):
    message = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)
    chat = models.ForeignKey(Chat, on_delete=models.DO_NOTHING)

    def __str__(self):
        return f'History of chat {self.chat}'

    class Meta:
        db_table = 'chat_history'
