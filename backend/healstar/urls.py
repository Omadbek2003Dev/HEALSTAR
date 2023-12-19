from django.contrib import admin
from django.urls import path, include
from django.conf import settings
from drf_yasg import openapi
from drf_yasg.views import get_schema_view
from rest_framework import permissions

admin.site.site_title = 'HealStar'


schema_view = get_schema_view(
    openapi.Info(
        title='Healstar',
        default_version='v1',
    ),
    public=True,
    permission_classes=[permissions.AllowAny],
)

routes = [
    path('chats/', include('chat.urls')),
    path('core/', include('core.urls')),
    path('users/', include('users.urls')),
]

urlpatterns = [
    path('admin/', admin.site.urls),
    path('api/', include(routes)),
    path('swagger/', schema_view.with_ui('swagger', cache_timeout=0), name='schema-swagger-ui'),
]
