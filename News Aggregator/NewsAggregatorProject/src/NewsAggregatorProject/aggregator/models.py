from django.db import models

class User(models.Model):
    isRegistered = models.BooleanField()
    isAdmin = models.BooleanField()
    user_name = models.CharField(max_length = 40)
    password = models.CharField(max_length = 20)
    rating = models.DecimalField(max_digits = 2, decimal_places = 1) # minimum 0, Maximum 5
    date_of_birth = models.DateField()
    email = models.EmailField()
    def __str__(self):
        return self.user_name
    
class Article(models.Model):
    author = models.ForeignKey(User)
    title = models.CharField(max_length = 100)
    text_description = models.CharField(max_length = 1024)
    created = models.DateTimeField()#make into DateField
    updated = models.DateTimeField()#make into DateField
    source_article = models.URLField()
    rating = models.DecimalField(max_digits = 2, decimal_places = 1) # minimum 0, Maximum 5
    def __str__(self):
        return '%s  Rating:%s' % (self.title, self.rating)
    
class Category(models.Model):
    name = models.CharField(max_length = 20)
    article_list = models.ManyToManyField(Article)
    def __str__(self):
        return self.name