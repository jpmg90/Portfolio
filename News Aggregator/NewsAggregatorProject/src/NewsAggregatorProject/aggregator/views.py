# Create your views here.
from django.shortcuts import render_to_response

from django.db.models import Q
from models import Article
from forms import ContactForm
from django.core.mail import send_mail
from django.http import HttpResponseRedirect

def base(request):
    return render_to_response('base_carl.html', locals())

def world(request):
    return render_to_response('world_carl.html', locals())

def login(request):
    return render_to_response('login_carl.html', locals())

def us(request):
    return render_to_response('us_carl.html', locals())

def politics(request):
    return render_to_response('politics_carl.html', locals())

def tech(request):
    return render_to_response('tech_carl.html', locals())

def sports(request):
    return render_to_response('sports_carl.html', locals())

def contact(request): 
    if request.method == 'POST':
        form = ContactForm(request.POST)
        if form.is_valid():
            topic = form.cleaned_data['topic']
            message = form.cleaned_data['message']
            sender = form.cleaned_data.get('sender', 'noreply@example.com')
            send_mail('Feedback from your site, topic: %s' % topic, 
                      message, 
                      sender, 
                      ['jpmg90@gmail.com'], 
                      fail_silently=False
                      )
            return HttpResponseRedirect('/contact/thanks/')
    else:
        form = ContactForm(initial={'sender': 'user@example.com'}) #set initial to the email to whoever is logged in
    return render_to_response('contact_carl.html', locals())

def thanks(request):
    return render_to_response('thanks_carl.html', locals())
    

def about(request):
    return render_to_response('about_carl.html', locals())


# NO longer useful
"""
def home(request):
    return render_to_response('base.html', locals())

def world1(request):
    variable = "This is Gay"
    return render_to_response('world.html', locals())

def search(request):
    query = request.GET.get('q', '')
    if query:
        qset = (
                Q(title__icontains = query) |
                Q(author__user_name__icontains = query)
                )
        results = Article.objects.filter(qset).distinct()
    else:
        results = []
    return render_to_response('articleSearch.html', locals())

def login1(request):
    return render_to_response('login.html', locals())

def about1(request):
    return render_to_response('about.html', locals())

def contact1(request): 
    if request.method == 'POST':
        form = ContactForm(request.POST)
        if form.is_valid():
            topic = form.cleaned_data['topic']
            message = form.cleaned_data['message']
            sender = form.cleaned_data.get('sender', 'noreply@example.com')
            send_mail('Feedback from your site, topic: %s' % topic, 
                      message, 
                      sender, 
                      ['jpmg90@gmail.com'], 
                      fail_silently=False
                      )
            return HttpResponseRedirect('/contact/thanks/')
    else:
        form = ContactForm(initial={'sender': 'user@example.com'}) 
    return render_to_response('contact.html', locals())

def thanks1(request):
    return render_to_response('thanks.html', locals())
"""