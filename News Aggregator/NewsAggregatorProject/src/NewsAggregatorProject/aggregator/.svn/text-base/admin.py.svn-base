from django.contrib import admin
from NewsAggregatorProject.aggregator.models import User, Article, Category

class UserAdmin(admin.ModelAdmin):
    pass
admin.site.register(User, UserAdmin)

class ArticleAdmin(admin.ModelAdmin):
    list_display = ('title', 'author', 'updated')
    list_filter = ('author', 'created', 'source_article')
    ordering = ('-updated',)
    search_fields = ('title',)
admin.site.register(Article, ArticleAdmin)

class CategoryAdmin(admin.ModelAdmin):
    pass
admin.site.register(Category, CategoryAdmin)