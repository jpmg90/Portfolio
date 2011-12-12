from django.conf.urls.defaults import patterns, include, url
#from NewsAggregatorProject.aggregator.views import home, world1, search, login1, about1, contact1, thanks 1
from NewsAggregatorProject.aggregator.views import base, world, login, us, politics, tech, sports, contact, thanks, about

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    url(r'^$', base),
    url(r'^world/$', world),
    url(r'^home/$', base),
    url(r'^login/$', login),
    url(r'^us/$', us),
    url(r'^politics/$', politics),
    url(r'^tech/$', tech),
    url(r'^sports/$', sports),
    url(r'^contact/$', contact),
    url(r'^contact/thanks/$', thanks),
    url(r'^about/$', about),
    
            
            
            
    # Old URLS             
    #url(r'^$', home),   
    #url(r'^home/$', home),   
    #url(r'^world1/$', world1),  
    #url(r'^search/$', search),
    #url(r'^login1/$', login1),
    #url(r'^about1/$', about1),
    #url(r'^contact1/$', contact1),
    #url(r'^contact1/thanks1/$', thanks1),
    # Examples:
    # url(r'^$', 'NewsAggregatorProject.views.home', name='home'),
    # url(r'^NewsAggregatorProject/', include('NewsAggregatorProject.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    url(r'^admin/', include(admin.site.urls)),
)
