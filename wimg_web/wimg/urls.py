from django.conf.urls import patterns, include, url

from wimg import views

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'wimg_web.views.home', name='home'),
    # url(r'^blog/', include('blog.urls'))

    url(r'^$', views.index, name = 'index'),
    url(r'^img/$', views.img, name = 'img'),
    url(r'^upload_page$', views.upload_page, name = 'upload_page'),
    url(r'^upload/$', views.upload, name = 'upload'),
)
